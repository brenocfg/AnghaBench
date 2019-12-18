#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ frame_irq; } ;
struct bttv {unsigned int input; unsigned int new_input; scalar_t__ tuner_type; int /*<<< orphan*/  audio_input; int /*<<< orphan*/  s_lock; TYPE_1__ curr; } ;

/* Variables and functions */
 scalar_t__ TUNER_ABSENT ; 
 int /*<<< orphan*/  TVAUDIO_INPUT_EXTERN ; 
 int /*<<< orphan*/  TVAUDIO_INPUT_TUNER ; 
 int /*<<< orphan*/  audio_input (struct bttv*,int /*<<< orphan*/ ) ; 
 scalar_t__ irq_iswitch ; 
 int /*<<< orphan*/  set_tvnorm (struct bttv*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  video_mux (struct bttv*,unsigned int) ; 

__attribute__((used)) static void
set_input(struct bttv *btv, unsigned int input, unsigned int norm)
{
	unsigned long flags;

	btv->input = input;
	if (irq_iswitch) {
		spin_lock_irqsave(&btv->s_lock,flags);
		if (btv->curr.frame_irq) {
			/* active capture -> delayed input switch */
			btv->new_input = input;
		} else {
			video_mux(btv,input);
		}
		spin_unlock_irqrestore(&btv->s_lock,flags);
	} else {
		video_mux(btv,input);
	}
	btv->audio_input = (btv->tuner_type != TUNER_ABSENT && input == 0) ?
				TVAUDIO_INPUT_TUNER : TVAUDIO_INPUT_EXTERN;
	audio_input(btv, btv->audio_input);
	set_tvnorm(btv, norm);
}
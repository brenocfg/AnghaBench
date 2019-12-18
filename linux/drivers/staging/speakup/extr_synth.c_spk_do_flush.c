#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flushing; } ;
struct TYPE_3__ {scalar_t__ alive; } ;

/* Variables and functions */
 int /*<<< orphan*/  speakup_event ; 
 TYPE_2__ speakup_info ; 
 int /*<<< orphan*/  speakup_task ; 
 int /*<<< orphan*/  spk_pitch_buff ; 
 scalar_t__ spk_pitch_shift ; 
 TYPE_1__* synth ; 
 int /*<<< orphan*/  synth_buffer_clear () ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void spk_do_flush(void)
{
	if (!synth)
		return;

	speakup_info.flushing = 1;
	synth_buffer_clear();
	if (synth->alive) {
		if (spk_pitch_shift) {
			synth_printf("%s", spk_pitch_buff);
			spk_pitch_shift = 0;
		}
	}
	wake_up_interruptible_all(&speakup_event);
	wake_up_process(speakup_task);
}
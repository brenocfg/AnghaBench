#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bttv {int has_radio_tuner; int /*<<< orphan*/  audio_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVAUDIO_INPUT_RADIO ; 
 int /*<<< orphan*/  audio_input (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_radio ; 
 int /*<<< orphan*/  tuner ; 

__attribute__((used)) static void radio_enable(struct bttv *btv)
{
	/* Switch to the radio tuner */
	if (!btv->has_radio_tuner) {
		btv->has_radio_tuner = 1;
		bttv_call_all(btv, tuner, s_radio);
		btv->audio_input = TVAUDIO_INPUT_RADIO;
		audio_input(btv, btv->audio_input);
	}
}
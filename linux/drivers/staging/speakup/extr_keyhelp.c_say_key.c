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

/* Variables and functions */
 scalar_t__ MSG_KEYNAMES_START ; 
 scalar_t__ MSG_STATES_START ; 
 int* masks ; 
 int num_key_names ; 
 int /*<<< orphan*/  spk_msg_get (scalar_t__) ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void say_key(int key)
{
	int i, state = key >> 8;

	key &= 0xff;
	for (i = 0; i < 6; i++) {
		if (state & masks[i])
			synth_printf(" %s", spk_msg_get(MSG_STATES_START + i));
	}
	if ((key > 0) && (key <= num_key_names))
		synth_printf(" %s\n",
			     spk_msg_get(MSG_KEYNAMES_START + (key - 1)));
}
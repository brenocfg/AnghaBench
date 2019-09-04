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
struct adp5588_kpad {int gpimapsize; int /*<<< orphan*/ * keycode; int /*<<< orphan*/  input; TYPE_1__* gpimap; int /*<<< orphan*/  client; } ;
struct TYPE_2__ {int pin; int /*<<< orphan*/  sw_evt; } ;

/* Variables and functions */
 int GPI_PIN_BASE ; 
 int GPI_PIN_END ; 
 int KEY_EV_MASK ; 
 int KEY_EV_PRESSED ; 
 scalar_t__ Key_EVENTA ; 
 int adp5588_read (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adp5588_report_events(struct adp5588_kpad *kpad, int ev_cnt)
{
	int i, j;

	for (i = 0; i < ev_cnt; i++) {
		int key = adp5588_read(kpad->client, Key_EVENTA + i);
		int key_val = key & KEY_EV_MASK;

		if (key_val >= GPI_PIN_BASE && key_val <= GPI_PIN_END) {
			for (j = 0; j < kpad->gpimapsize; j++) {
				if (key_val == kpad->gpimap[j].pin) {
					input_report_switch(kpad->input,
							kpad->gpimap[j].sw_evt,
							key & KEY_EV_PRESSED);
					break;
				}
			}
		} else {
			input_report_key(kpad->input,
					 kpad->keycode[key_val - 1],
					 key & KEY_EV_PRESSED);
		}
	}
}
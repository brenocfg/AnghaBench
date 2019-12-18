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
struct adp5589_kpad {int gpimapsize; TYPE_1__* gpimap; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {int pin; int /*<<< orphan*/  sw_evt; } ;

/* Variables and functions */
 int KEY_EV_PRESSED ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adp5589_report_switches(struct adp5589_kpad *kpad,
				    int key, int key_val)
{
	int i;

	for (i = 0; i < kpad->gpimapsize; i++) {
		if (key_val == kpad->gpimap[i].pin) {
			input_report_switch(kpad->input,
					    kpad->gpimap[i].sw_evt,
					    key & KEY_EV_PRESSED);
			break;
		}
	}
}
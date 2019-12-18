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
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned short,int) ; 

__attribute__((used)) static void tegra_kbc_report_pressed_keys(struct input_dev *input,
					  unsigned char scancodes[],
					  unsigned short keycodes[],
					  unsigned int num_pressed_keys)
{
	unsigned int i;

	for (i = 0; i < num_pressed_keys; i++) {
		input_event(input, EV_MSC, MSC_SCAN, scancodes[i]);
		input_report_key(input, keycodes[i], 1);
	}
}
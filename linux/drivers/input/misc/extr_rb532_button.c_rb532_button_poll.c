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
struct input_polled_dev {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB532_BTN_KSYM ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb532_button_pressed () ; 

__attribute__((used)) static void rb532_button_poll(struct input_polled_dev *poll_dev)
{
	input_report_key(poll_dev->input, RB532_BTN_KSYM,
			 rb532_button_pressed());
	input_sync(poll_dev->input);
}
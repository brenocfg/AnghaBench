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
struct pwc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWC_TRACE (char*) ; 

__attribute__((used)) static void pwc_snapshot_button(struct pwc_device *pdev, int down)
{
	if (down) {
		PWC_TRACE("Snapshot button pressed.\n");
	} else {
		PWC_TRACE("Snapshot button released.\n");
	}

#ifdef CONFIG_USB_PWC_INPUT_EVDEV
	if (pdev->button_dev) {
		input_report_key(pdev->button_dev, KEY_CAMERA, down);
		input_sync(pdev->button_dev);
	}
#endif
}
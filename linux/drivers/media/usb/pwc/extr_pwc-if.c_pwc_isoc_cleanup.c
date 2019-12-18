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
struct pwc_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWC_DEBUG_OPEN (char*) ; 
 int /*<<< orphan*/  pwc_iso_free (struct pwc_device*) ; 
 int /*<<< orphan*/  pwc_iso_stop (struct pwc_device*) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwc_isoc_cleanup(struct pwc_device *pdev)
{
	PWC_DEBUG_OPEN(">> pwc_isoc_cleanup()\n");

	pwc_iso_stop(pdev);
	pwc_iso_free(pdev);
	usb_set_interface(pdev->udev, 0, 0);

	PWC_DEBUG_OPEN("<< pwc_isoc_cleanup()\n");
}
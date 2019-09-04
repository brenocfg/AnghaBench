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
struct platform_device {int dummy; } ;
struct palmas_usb {int /*<<< orphan*/  wq_detectid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct palmas_usb* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int palmas_usb_remove(struct platform_device *pdev)
{
	struct palmas_usb *palmas_usb = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&palmas_usb->wq_detectid);

	return 0;
}
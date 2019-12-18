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
struct platform_device {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 

void ci_hdrc_remove_device(struct platform_device *pdev)
{
	int id = pdev->id;
	platform_device_unregister(pdev);
	ida_simple_remove(&ci_ida, id);
}
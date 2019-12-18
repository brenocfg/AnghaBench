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
struct sm501_devdata {int dummy; } ;
struct platform_device {int /*<<< orphan*/ * resource; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  sm501_create_irq (struct sm501_devdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sm501_create_mem (struct sm501_devdata*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct platform_device* sm501_create_subdev (struct sm501_devdata*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm501_create_subio (struct sm501_devdata*,int /*<<< orphan*/ *,int,int) ; 
 int sm501_register_device (struct sm501_devdata*,struct platform_device*) ; 

__attribute__((used)) static int sm501_register_usbhost(struct sm501_devdata *sm,
				  resource_size_t *mem_avail)
{
	struct platform_device *pdev;

	pdev = sm501_create_subdev(sm, "sm501-usb", 3, 0);
	if (!pdev)
		return -ENOMEM;

	sm501_create_subio(sm, &pdev->resource[0], 0x40000, 0x20000);
	sm501_create_mem(sm, &pdev->resource[1], mem_avail, 256*1024);
	sm501_create_irq(sm, &pdev->resource[2]);

	return sm501_register_device(sm, pdev);
}
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
struct TYPE_2__ {scalar_t__ start; } ;
struct zorro_dev {TYPE_1__ resource; } ;
struct xsurf100_ax_plat_data {int /*<<< orphan*/  data_area; int /*<<< orphan*/  base_regs; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ XS100_8390_DATA32_BASE ; 
 int XS100_8390_DATA32_SIZE ; 
 struct xsurf100_ax_plat_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int) ; 
 struct platform_device* zorro_get_drvdata (struct zorro_dev*) ; 

__attribute__((used)) static void xsurf100_remove(struct zorro_dev *zdev)
{
	struct platform_device *pdev = zorro_get_drvdata(zdev);
	struct xsurf100_ax_plat_data *xs100 = dev_get_platdata(&pdev->dev);

	platform_device_unregister(pdev);

	iounmap(xs100->base_regs);
	release_mem_region(zdev->resource.start, 0x100);
	iounmap(xs100->data_area);
	release_mem_region(zdev->resource.start + XS100_8390_DATA32_BASE,
			   XS100_8390_DATA32_SIZE);
}
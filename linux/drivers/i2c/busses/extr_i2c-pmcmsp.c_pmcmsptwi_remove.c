#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ iobase; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ MSP_TWI_INT_MSK_REG_OFFSET ; 
 int /*<<< orphan*/  free_irq (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcmsptwi_adapter ; 
 TYPE_1__ pmcmsptwi_data ; 
 int /*<<< orphan*/  pmcmsptwi_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int pmcmsptwi_remove(struct platform_device *pldev)
{
	struct resource *res;

	i2c_del_adapter(&pmcmsptwi_adapter);

	if (pmcmsptwi_data.irq) {
		pmcmsptwi_writel(0,
			pmcmsptwi_data.iobase + MSP_TWI_INT_MSK_REG_OFFSET);
		free_irq(pmcmsptwi_data.irq, &pmcmsptwi_data);
	}

	iounmap(pmcmsptwi_data.iobase);

	res = platform_get_resource(pldev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	return 0;
}
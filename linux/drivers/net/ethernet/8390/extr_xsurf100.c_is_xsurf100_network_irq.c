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
struct xsurf100_ax_plat_data {scalar_t__ base_regs; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ XS100_IRQSTATUS_BASE ; 
 struct xsurf100_ax_plat_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static int is_xsurf100_network_irq(struct platform_device *pdev)
{
	struct xsurf100_ax_plat_data *xs100 = dev_get_platdata(&pdev->dev);

	return (readw(xs100->base_regs + XS100_IRQSTATUS_BASE) & 0xaaaa) != 0;
}
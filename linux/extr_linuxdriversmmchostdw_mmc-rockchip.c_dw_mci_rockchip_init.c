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
struct dw_mci {int sdio_id0; int /*<<< orphan*/  bus_hz; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK3288_CLKGEN_DIV ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dw_mci_rockchip_init(struct dw_mci *host)
{
	/* It is slot 8 on Rockchip SoCs */
	host->sdio_id0 = 8;

	if (of_device_is_compatible(host->dev->of_node,
				    "rockchip,rk3288-dw-mshc"))
		host->bus_hz /= RK3288_CLKGEN_DIV;

	return 0;
}
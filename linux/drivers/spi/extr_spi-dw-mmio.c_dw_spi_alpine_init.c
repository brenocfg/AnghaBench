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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int cs_override; } ;
struct dw_spi_mmio {TYPE_1__ dws; } ;

/* Variables and functions */

__attribute__((used)) static int dw_spi_alpine_init(struct platform_device *pdev,
			      struct dw_spi_mmio *dwsmmio)
{
	dwsmmio->dws.cs_override = 1;

	return 0;
}
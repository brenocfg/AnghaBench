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
struct pl08x_driver_data {scalar_t__ base; TYPE_1__* vd; } ;
struct TYPE_2__ {scalar_t__ ftdmac020; scalar_t__ nomadik; } ;

/* Variables and functions */
 scalar_t__ FTDMAC020_CSR ; 
 scalar_t__ PL080_CONFIG ; 
 int /*<<< orphan*/  PL080_CONFIG_ENABLE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pl08x_ensure_on(struct pl08x_driver_data *pl08x)
{
	/* The Nomadik variant does not have the config register */
	if (pl08x->vd->nomadik)
		return;
	/* The FTDMAC020 variant does this in another register */
	if (pl08x->vd->ftdmac020) {
		writel(PL080_CONFIG_ENABLE, pl08x->base + FTDMAC020_CSR);
		return;
	}
	writel(PL080_CONFIG_ENABLE, pl08x->base + PL080_CONFIG);
}
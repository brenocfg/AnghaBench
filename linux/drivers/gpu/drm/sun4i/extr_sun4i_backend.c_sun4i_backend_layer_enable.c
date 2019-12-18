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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;
struct sun4i_backend {TYPE_1__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*,int) ; 
 scalar_t__ SUN4I_BACKEND_MODCTL_LAY_EN (int) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_MODCTL_REG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void sun4i_backend_layer_enable(struct sun4i_backend *backend,
				int layer, bool enable)
{
	u32 val;

	DRM_DEBUG_DRIVER("%sabling layer %d\n", enable ? "En" : "Dis",
			 layer);

	if (enable)
		val = SUN4I_BACKEND_MODCTL_LAY_EN(layer);
	else
		val = 0;

	regmap_update_bits(backend->engine.regs, SUN4I_BACKEND_MODCTL_REG,
			   SUN4I_BACKEND_MODCTL_LAY_EN(layer), val);
}
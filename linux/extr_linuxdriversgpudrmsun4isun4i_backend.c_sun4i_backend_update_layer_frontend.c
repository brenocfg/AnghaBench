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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;
struct sun4i_backend {TYPE_1__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_ATTCTL_REG0 (int) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_ATTCTL_REG0_LAY_VDOEN ; 
 int /*<<< orphan*/  SUN4I_BACKEND_ATTCTL_REG1 (int) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_ATTCTL_REG1_LAY_FBFMT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sun4i_backend_drm_format_to_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sun4i_backend_update_layer_frontend(struct sun4i_backend *backend,
					int layer, uint32_t fmt)
{
	u32 val;
	int ret;

	ret = sun4i_backend_drm_format_to_layer(fmt, &val);
	if (ret) {
		DRM_DEBUG_DRIVER("Invalid format\n");
		return ret;
	}

	regmap_update_bits(backend->engine.regs,
			   SUN4I_BACKEND_ATTCTL_REG0(layer),
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_VDOEN,
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_VDOEN);

	regmap_update_bits(backend->engine.regs,
			   SUN4I_BACKEND_ATTCTL_REG1(layer),
			   SUN4I_BACKEND_ATTCTL_REG1_LAY_FBFMT, val);

	return 0;
}
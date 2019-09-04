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
struct sunxi_engine {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_OCCTL_ENABLE ; 
 int /*<<< orphan*/  SUN4I_BACKEND_OCCTL_REG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_backend_disable_color_correction(struct sunxi_engine *engine)
{
	DRM_DEBUG_DRIVER("Disabling color correction\n");

	/* Disable color correction */
	regmap_update_bits(engine->regs, SUN4I_BACKEND_OCCTL_REG,
			   SUN4I_BACKEND_OCCTL_ENABLE, 0);
}
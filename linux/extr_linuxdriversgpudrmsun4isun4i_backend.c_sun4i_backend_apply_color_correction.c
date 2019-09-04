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
 int /*<<< orphan*/  SUN4I_BACKEND_OCRCOEF_REG (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sunxi_rgb2yuv_coef ; 

__attribute__((used)) static void sun4i_backend_apply_color_correction(struct sunxi_engine *engine)
{
	int i;

	DRM_DEBUG_DRIVER("Applying RGB to YUV color correction\n");

	/* Set color correction */
	regmap_write(engine->regs, SUN4I_BACKEND_OCCTL_REG,
		     SUN4I_BACKEND_OCCTL_ENABLE);

	for (i = 0; i < 12; i++)
		regmap_write(engine->regs, SUN4I_BACKEND_OCRCOEF_REG(i),
			     sunxi_rgb2yuv_coef[i]);
}
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
struct zx_vga_pwrctrl {int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;
struct zx_vga {struct zx_vga_pwrctrl pwrctrl; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOU_VGA ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zx_vga* to_zx_vga (struct drm_encoder*) ; 
 int /*<<< orphan*/  vou_inf_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zx_vga_encoder_disable(struct drm_encoder *encoder)
{
	struct zx_vga *vga = to_zx_vga(encoder);
	struct zx_vga_pwrctrl *pwrctrl = &vga->pwrctrl;

	vou_inf_disable(VOU_VGA, encoder->crtc);

	/* Clear bit to power down VGA DACs */
	regmap_update_bits(pwrctrl->regmap, pwrctrl->reg, pwrctrl->mask, 0);
}
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
struct zx_tvenc_pwrctrl {int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;
struct zx_tvenc {scalar_t__ mmio; struct zx_tvenc_pwrctrl pwrctrl; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 scalar_t__ VENC_ENABLE ; 
 int /*<<< orphan*/  VOU_TV_ENC ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zx_tvenc* to_zx_tvenc (struct drm_encoder*) ; 
 int /*<<< orphan*/  vou_inf_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zx_tvenc_encoder_disable(struct drm_encoder *encoder)
{
	struct zx_tvenc *tvenc = to_zx_tvenc(encoder);
	struct zx_tvenc_pwrctrl *pwrctrl = &tvenc->pwrctrl;

	zx_writel(tvenc->mmio + VENC_ENABLE, 0);

	vou_inf_disable(VOU_TV_ENC, encoder->crtc);

	/* Clear bit to power down TVENC DAC */
	regmap_update_bits(pwrctrl->regmap, pwrctrl->reg, pwrctrl->mask, 0);
}
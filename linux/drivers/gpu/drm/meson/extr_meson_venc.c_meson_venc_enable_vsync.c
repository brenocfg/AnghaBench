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
struct meson_drm {int /*<<< orphan*/  hhi; scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  HHI_GCLK_MPEG2 ; 
 int /*<<< orphan*/  VENC_INTCTRL ; 
 int /*<<< orphan*/  VENC_INTCTRL_ENCI_LNRST_INT_EN ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void meson_venc_enable_vsync(struct meson_drm *priv)
{
	writel_relaxed(VENC_INTCTRL_ENCI_LNRST_INT_EN,
		       priv->io_base + _REG(VENC_INTCTRL));
	regmap_update_bits(priv->hhi, HHI_GCLK_MPEG2, BIT(25), BIT(25));
}
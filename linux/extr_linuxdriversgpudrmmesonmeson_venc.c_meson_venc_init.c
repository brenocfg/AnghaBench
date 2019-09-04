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
struct TYPE_2__ {int /*<<< orphan*/  current_mode; } ;
struct meson_drm {TYPE_1__ venc; scalar_t__ io_base; int /*<<< orphan*/  hhi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENCI_VIDEO_EN ; 
 int /*<<< orphan*/  ENCL_VIDEO_EN ; 
 int /*<<< orphan*/  ENCP_VIDEO_EN ; 
 int /*<<< orphan*/  HHI_HDMI_PHY_CNTL0 ; 
 int /*<<< orphan*/  HHI_VDAC_CNTL0 ; 
 int /*<<< orphan*/  HHI_VDAC_CNTL1 ; 
 int /*<<< orphan*/  MESON_VENC_MODE_NONE ; 
 int /*<<< orphan*/  VENC_VDAC_SETTING ; 
 int /*<<< orphan*/  VPU_HDMI_SETTING ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_venc_disable_vsync (struct meson_drm*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void meson_venc_init(struct meson_drm *priv)
{
	/* Disable CVBS VDAC */
	regmap_write(priv->hhi, HHI_VDAC_CNTL0, 0);
	regmap_write(priv->hhi, HHI_VDAC_CNTL1, 8);

	/* Power Down Dacs */
	writel_relaxed(0xff, priv->io_base + _REG(VENC_VDAC_SETTING));

	/* Disable HDMI PHY */
	regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0);

	/* Disable HDMI */
	writel_bits_relaxed(0x3, 0,
			    priv->io_base + _REG(VPU_HDMI_SETTING));

	/* Disable all encoders */
	writel_relaxed(0, priv->io_base + _REG(ENCI_VIDEO_EN));
	writel_relaxed(0, priv->io_base + _REG(ENCP_VIDEO_EN));
	writel_relaxed(0, priv->io_base + _REG(ENCL_VIDEO_EN));

	/* Disable VSync IRQ */
	meson_venc_disable_vsync(priv);

	priv->venc.current_mode = MESON_VENC_MODE_NONE;
}
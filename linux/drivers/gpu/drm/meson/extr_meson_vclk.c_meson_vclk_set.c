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
struct meson_drm {int /*<<< orphan*/  hhi; } ;

/* Variables and functions */
 int CTS_ENCI_EN ; 
 int CTS_ENCI_SEL_MASK ; 
 int CTS_ENCI_SEL_SHIFT ; 
 int CTS_ENCP_EN ; 
 int CTS_ENCP_SEL_MASK ; 
 int CTS_ENCP_SEL_SHIFT ; 
 int CTS_HDMI_SYS_DIV_MASK ; 
 int CTS_HDMI_SYS_EN ; 
 int CTS_HDMI_SYS_SEL_MASK ; 
 int HDMI_TX_PIXEL_EN ; 
 int HDMI_TX_PIXEL_SEL_MASK ; 
 int HDMI_TX_PIXEL_SEL_SHIFT ; 
 int /*<<< orphan*/  HHI_HDMI_CLK_CNTL ; 
 int /*<<< orphan*/  HHI_VID_CLK_CNTL ; 
 int /*<<< orphan*/  HHI_VID_CLK_CNTL2 ; 
 int /*<<< orphan*/  HHI_VID_CLK_DIV ; 
 int VCLK_DIV12_EN ; 
 int VCLK_DIV1_EN ; 
 int VCLK_DIV2_EN ; 
 int VCLK_DIV4_EN ; 
 int VCLK_DIV6_EN ; 
 int VCLK_DIV_MASK ; 
 int VCLK_EN ; 
 int VCLK_SEL_MASK ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_G12A ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXBB ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXL ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXM ; 
 int /*<<< orphan*/  meson_hdmi_pll_generic_set (struct meson_drm*,unsigned int) ; 
 int /*<<< orphan*/  meson_hdmi_pll_set_params (struct meson_drm*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  meson_vid_pll_set (struct meson_drm*,unsigned int) ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void meson_vclk_set(struct meson_drm *priv, unsigned int pll_base_freq,
			   unsigned int od1, unsigned int od2, unsigned int od3,
			   unsigned int vid_pll_div, unsigned int vclk_div,
			   unsigned int hdmi_tx_div, unsigned int venc_div,
			   bool hdmi_use_enci, bool vic_alternate_clock)
{
	unsigned int m = 0, frac = 0;

	/* Set HDMI-TX sys clock */
	regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			   CTS_HDMI_SYS_SEL_MASK, 0);
	regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			   CTS_HDMI_SYS_DIV_MASK, 0);
	regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			   CTS_HDMI_SYS_EN, CTS_HDMI_SYS_EN);

	/* Set HDMI PLL rate */
	if (!od1 && !od2 && !od3) {
		meson_hdmi_pll_generic_set(priv, pll_base_freq);
	} else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB)) {
		switch (pll_base_freq) {
		case 2970000:
			m = 0x3d;
			frac = vic_alternate_clock ? 0xd02 : 0xe00;
			break;
		case 4320000:
			m = vic_alternate_clock ? 0x59 : 0x5a;
			frac = vic_alternate_clock ? 0xe8f : 0;
			break;
		case 5940000:
			m = 0x7b;
			frac = vic_alternate_clock ? 0xa05 : 0xc00;
			break;
		}

		meson_hdmi_pll_set_params(priv, m, frac, od1, od2, od3);
	} else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		   meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL)) {
		switch (pll_base_freq) {
		case 2970000:
			m = 0x7b;
			frac = vic_alternate_clock ? 0x281 : 0x300;
			break;
		case 4320000:
			m = vic_alternate_clock ? 0xb3 : 0xb4;
			frac = vic_alternate_clock ? 0x347 : 0;
			break;
		case 5940000:
			m = 0xf7;
			frac = vic_alternate_clock ? 0x102 : 0x200;
			break;
		}

		meson_hdmi_pll_set_params(priv, m, frac, od1, od2, od3);
	} else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) {
		switch (pll_base_freq) {
		case 2970000:
			m = 0x7b;
			frac = vic_alternate_clock ? 0x140b4 : 0x18000;
			break;
		case 4320000:
			m = vic_alternate_clock ? 0xb3 : 0xb4;
			frac = vic_alternate_clock ? 0x1a3ee : 0;
			break;
		case 5940000:
			m = 0xf7;
			frac = vic_alternate_clock ? 0x8148 : 0x10000;
			break;
		}

		meson_hdmi_pll_set_params(priv, m, frac, od1, od2, od3);
	}

	/* Setup vid_pll divider */
	meson_vid_pll_set(priv, vid_pll_div);

	/* Set VCLK div */
	regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
			   VCLK_SEL_MASK, 0);
	regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
			   VCLK_DIV_MASK, vclk_div - 1);

	/* Set HDMI-TX source */
	switch (hdmi_tx_div) {
	case 1:
		/* enable vclk_div1 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV1_EN, VCLK_DIV1_EN);

		/* select vclk_div1 for HDMI-TX */
		regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
				   HDMI_TX_PIXEL_SEL_MASK, 0);
		break;
	case 2:
		/* enable vclk_div2 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV2_EN, VCLK_DIV2_EN);

		/* select vclk_div2 for HDMI-TX */
		regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			HDMI_TX_PIXEL_SEL_MASK, 1 << HDMI_TX_PIXEL_SEL_SHIFT);
		break;
	case 4:
		/* enable vclk_div4 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV4_EN, VCLK_DIV4_EN);

		/* select vclk_div4 for HDMI-TX */
		regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			HDMI_TX_PIXEL_SEL_MASK, 2 << HDMI_TX_PIXEL_SEL_SHIFT);
		break;
	case 6:
		/* enable vclk_div6 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV6_EN, VCLK_DIV6_EN);

		/* select vclk_div6 for HDMI-TX */
		regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			HDMI_TX_PIXEL_SEL_MASK, 3 << HDMI_TX_PIXEL_SEL_SHIFT);
		break;
	case 12:
		/* enable vclk_div12 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV12_EN, VCLK_DIV12_EN);

		/* select vclk_div12 for HDMI-TX */
		regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			HDMI_TX_PIXEL_SEL_MASK, 4 << HDMI_TX_PIXEL_SEL_SHIFT);
		break;
	}
	regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL2,
				   HDMI_TX_PIXEL_EN, HDMI_TX_PIXEL_EN);

	/* Set ENCI/ENCP Source */
	switch (venc_div) {
	case 1:
		/* enable vclk_div1 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV1_EN, VCLK_DIV1_EN);

		if (hdmi_use_enci)
			/* select vclk_div1 for enci */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
					   CTS_ENCI_SEL_MASK, 0);
		else
			/* select vclk_div1 for encp */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
					   CTS_ENCP_SEL_MASK, 0);
		break;
	case 2:
		/* enable vclk_div2 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV2_EN, VCLK_DIV2_EN);

		if (hdmi_use_enci)
			/* select vclk_div2 for enci */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCI_SEL_MASK, 1 << CTS_ENCI_SEL_SHIFT);
		else
			/* select vclk_div2 for encp */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCP_SEL_MASK, 1 << CTS_ENCP_SEL_SHIFT);
		break;
	case 4:
		/* enable vclk_div4 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV4_EN, VCLK_DIV4_EN);

		if (hdmi_use_enci)
			/* select vclk_div4 for enci */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCI_SEL_MASK, 2 << CTS_ENCI_SEL_SHIFT);
		else
			/* select vclk_div4 for encp */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCP_SEL_MASK, 2 << CTS_ENCP_SEL_SHIFT);
		break;
	case 6:
		/* enable vclk_div6 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV6_EN, VCLK_DIV6_EN);

		if (hdmi_use_enci)
			/* select vclk_div6 for enci */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCI_SEL_MASK, 3 << CTS_ENCI_SEL_SHIFT);
		else
			/* select vclk_div6 for encp */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCP_SEL_MASK, 3 << CTS_ENCP_SEL_SHIFT);
		break;
	case 12:
		/* enable vclk_div12 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV12_EN, VCLK_DIV12_EN);

		if (hdmi_use_enci)
			/* select vclk_div12 for enci */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCI_SEL_MASK, 4 << CTS_ENCI_SEL_SHIFT);
		else
			/* select vclk_div12 for encp */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCP_SEL_MASK, 4 << CTS_ENCP_SEL_SHIFT);
		break;
	}

	if (hdmi_use_enci)
		/* Enable ENCI clock gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL2,
				   CTS_ENCI_EN, CTS_ENCI_EN);
	else
		/* Enable ENCP clock gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL2,
				   CTS_ENCP_EN, CTS_ENCP_EN);

	regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL, VCLK_EN, VCLK_EN);
}
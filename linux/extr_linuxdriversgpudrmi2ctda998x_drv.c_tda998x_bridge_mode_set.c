#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_6__ {scalar_t__ format; } ;
struct TYPE_4__ {int cea_rev; } ;
struct TYPE_5__ {TYPE_1__ display_info; } ;
struct tda998x_priv {scalar_t__ rev; unsigned long tmds_clock; int supports_infoframes; int /*<<< orphan*/  audio_mutex; TYPE_3__ audio_params; scalar_t__ sink_has_audio; TYPE_2__ connector; } ;
struct drm_display_mode {int htotal; int vtotal; int hsync_end; int hdisplay; int hsync_start; int flags; int hskew; int vsync_start; int vdisplay; int vsync_end; unsigned long clock; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 scalar_t__ AFMT_UNUSED ; 
 int AIP_CNTRL_0_RST_FIFO ; 
 int DRM_MODE_FLAG_HSKEW ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int ENC_CNTRL_CTL_CODE (int) ; 
 int FEAT_POWERDOWN_CSC ; 
 int FEAT_POWERDOWN_PREFILT ; 
 int HVF_CNTRL_0_INTPOL (int /*<<< orphan*/ ) ; 
 int HVF_CNTRL_0_PREFIL (int /*<<< orphan*/ ) ; 
 int HVF_CNTRL_1_VQR (int /*<<< orphan*/ ) ; 
 int MAT_CONTRL_MAT_BP ; 
 int MAT_CONTRL_MAT_SC (int) ; 
 int PLL_SERIAL_1_SRL_MAN_IZ ; 
 int PLL_SERIAL_2_SRL_NOSC (int) ; 
 int PLL_SERIAL_2_SRL_PR (int) ; 
 int PLL_SERIAL_3_SRL_CCIR ; 
 int PLL_SERIAL_3_SRL_DE ; 
 int /*<<< orphan*/  REG_AIP_CNTRL_0 ; 
 int /*<<< orphan*/  REG_ANA_GENERAL ; 
 int /*<<< orphan*/  REG_DE_START_MSB ; 
 int /*<<< orphan*/  REG_DE_STOP_MSB ; 
 int /*<<< orphan*/  REG_ENABLE_SPACE ; 
 int /*<<< orphan*/  REG_ENC_CNTRL ; 
 int /*<<< orphan*/  REG_FEAT_POWERDOWN ; 
 int /*<<< orphan*/  REG_HS_PIX_START_MSB ; 
 int /*<<< orphan*/  REG_HS_PIX_STOP_MSB ; 
 int /*<<< orphan*/  REG_HVF_CNTRL_0 ; 
 int /*<<< orphan*/  REG_HVF_CNTRL_1 ; 
 int /*<<< orphan*/  REG_MAT_CONTRL ; 
 int /*<<< orphan*/  REG_NLINE_MSB ; 
 int /*<<< orphan*/  REG_NPIX_MSB ; 
 int /*<<< orphan*/  REG_PLL_SERIAL_1 ; 
 int /*<<< orphan*/  REG_PLL_SERIAL_2 ; 
 int /*<<< orphan*/  REG_PLL_SERIAL_3 ; 
 int /*<<< orphan*/  REG_REFLINE_MSB ; 
 int /*<<< orphan*/  REG_REFPIX_MSB ; 
 int /*<<< orphan*/  REG_RPT_CNTRL ; 
 int /*<<< orphan*/  REG_SEL_CLK ; 
 int /*<<< orphan*/  REG_SERIALIZER ; 
 int /*<<< orphan*/  REG_TBG_CNTRL_0 ; 
 int /*<<< orphan*/  REG_TBG_CNTRL_1 ; 
 int /*<<< orphan*/  REG_TX33 ; 
 int /*<<< orphan*/  REG_VIDFORMAT ; 
 int /*<<< orphan*/  REG_VIP_CNTRL_3 ; 
 int /*<<< orphan*/  REG_VIP_CNTRL_4 ; 
 int /*<<< orphan*/  REG_VIP_CNTRL_5 ; 
 int /*<<< orphan*/  REG_VS_LINE_END_1_MSB ; 
 int /*<<< orphan*/  REG_VS_LINE_END_2_MSB ; 
 int /*<<< orphan*/  REG_VS_LINE_STRT_1_MSB ; 
 int /*<<< orphan*/  REG_VS_LINE_STRT_2_MSB ; 
 int /*<<< orphan*/  REG_VS_PIX_END_1_MSB ; 
 int /*<<< orphan*/  REG_VS_PIX_END_2_MSB ; 
 int /*<<< orphan*/  REG_VS_PIX_STRT_1_MSB ; 
 int /*<<< orphan*/  REG_VS_PIX_STRT_2_MSB ; 
 int /*<<< orphan*/  REG_VWIN_END_1_MSB ; 
 int /*<<< orphan*/  REG_VWIN_END_2_MSB ; 
 int /*<<< orphan*/  REG_VWIN_START_1_MSB ; 
 int /*<<< orphan*/  REG_VWIN_START_2_MSB ; 
 int SEL_CLK_ENA_SC_CLK ; 
 int SEL_CLK_SEL_CLK1 ; 
 int SEL_CLK_SEL_VRF_CLK (int /*<<< orphan*/ ) ; 
 int TBG_CNTRL_1_DWIN_DIS ; 
 int TBG_CNTRL_1_H_TGL ; 
 int TBG_CNTRL_1_TGL_EN ; 
 int TBG_CNTRL_1_V_TGL ; 
 scalar_t__ TDA19988 ; 
 int TX33_HDMI ; 
 int VIP_CNTRL_3_H_TGL ; 
 int VIP_CNTRL_3_SYNC_HS ; 
 int VIP_CNTRL_3_V_TGL ; 
 int VIP_CNTRL_4_BLANKIT (int /*<<< orphan*/ ) ; 
 int VIP_CNTRL_4_BLC (int /*<<< orphan*/ ) ; 
 int VIP_CNTRL_5_SP_CNT (int /*<<< orphan*/ ) ; 
 struct tda998x_priv* bridge_to_tda998x_priv (struct drm_bridge*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_clear (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_set (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_write (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_write16 (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda998x_configure_audio (struct tda998x_priv*,TYPE_3__*) ; 
 int /*<<< orphan*/  tda998x_write_avi (struct tda998x_priv*,struct drm_display_mode*) ; 

__attribute__((used)) static void tda998x_bridge_mode_set(struct drm_bridge *bridge,
				    struct drm_display_mode *mode,
				    struct drm_display_mode *adjusted_mode)
{
	struct tda998x_priv *priv = bridge_to_tda998x_priv(bridge);
	unsigned long tmds_clock;
	u16 ref_pix, ref_line, n_pix, n_line;
	u16 hs_pix_s, hs_pix_e;
	u16 vs1_pix_s, vs1_pix_e, vs1_line_s, vs1_line_e;
	u16 vs2_pix_s, vs2_pix_e, vs2_line_s, vs2_line_e;
	u16 vwin1_line_s, vwin1_line_e;
	u16 vwin2_line_s, vwin2_line_e;
	u16 de_pix_s, de_pix_e;
	u8 reg, div, rep;

	/*
	 * Internally TDA998x is using ITU-R BT.656 style sync but
	 * we get VESA style sync. TDA998x is using a reference pixel
	 * relative to ITU to sync to the input frame and for output
	 * sync generation. Currently, we are using reference detection
	 * from HS/VS, i.e. REFPIX/REFLINE denote frame start sync point
	 * which is position of rising VS with coincident rising HS.
	 *
	 * Now there is some issues to take care of:
	 * - HDMI data islands require sync-before-active
	 * - TDA998x register values must be > 0 to be enabled
	 * - REFLINE needs an additional offset of +1
	 * - REFPIX needs an addtional offset of +1 for UYUV and +3 for RGB
	 *
	 * So we add +1 to all horizontal and vertical register values,
	 * plus an additional +3 for REFPIX as we are using RGB input only.
	 */
	n_pix        = mode->htotal;
	n_line       = mode->vtotal;

	hs_pix_e     = mode->hsync_end - mode->hdisplay;
	hs_pix_s     = mode->hsync_start - mode->hdisplay;
	de_pix_e     = mode->htotal;
	de_pix_s     = mode->htotal - mode->hdisplay;
	ref_pix      = 3 + hs_pix_s;

	/*
	 * Attached LCD controllers may generate broken sync. Allow
	 * those to adjust the position of the rising VS edge by adding
	 * HSKEW to ref_pix.
	 */
	if (adjusted_mode->flags & DRM_MODE_FLAG_HSKEW)
		ref_pix += adjusted_mode->hskew;

	if ((mode->flags & DRM_MODE_FLAG_INTERLACE) == 0) {
		ref_line     = 1 + mode->vsync_start - mode->vdisplay;
		vwin1_line_s = mode->vtotal - mode->vdisplay - 1;
		vwin1_line_e = vwin1_line_s + mode->vdisplay;
		vs1_pix_s    = vs1_pix_e = hs_pix_s;
		vs1_line_s   = mode->vsync_start - mode->vdisplay;
		vs1_line_e   = vs1_line_s +
			       mode->vsync_end - mode->vsync_start;
		vwin2_line_s = vwin2_line_e = 0;
		vs2_pix_s    = vs2_pix_e  = 0;
		vs2_line_s   = vs2_line_e = 0;
	} else {
		ref_line     = 1 + (mode->vsync_start - mode->vdisplay)/2;
		vwin1_line_s = (mode->vtotal - mode->vdisplay)/2;
		vwin1_line_e = vwin1_line_s + mode->vdisplay/2;
		vs1_pix_s    = vs1_pix_e = hs_pix_s;
		vs1_line_s   = (mode->vsync_start - mode->vdisplay)/2;
		vs1_line_e   = vs1_line_s +
			       (mode->vsync_end - mode->vsync_start)/2;
		vwin2_line_s = vwin1_line_s + mode->vtotal/2;
		vwin2_line_e = vwin2_line_s + mode->vdisplay/2;
		vs2_pix_s    = vs2_pix_e = hs_pix_s + mode->htotal/2;
		vs2_line_s   = vs1_line_s + mode->vtotal/2 ;
		vs2_line_e   = vs2_line_s +
			       (mode->vsync_end - mode->vsync_start)/2;
	}

	tmds_clock = mode->clock;

	/*
	 * The divisor is power-of-2. The TDA9983B datasheet gives
	 * this as ranges of Msample/s, which is 10x the TMDS clock:
	 *   0 - 800 to 1500 Msample/s
	 *   1 - 400 to 800 Msample/s
	 *   2 - 200 to 400 Msample/s
	 *   3 - as 2 above
	 */
	for (div = 0; div < 3; div++)
		if (80000 >> div <= tmds_clock)
			break;

	mutex_lock(&priv->audio_mutex);

	/* mute the audio FIFO: */
	reg_set(priv, REG_AIP_CNTRL_0, AIP_CNTRL_0_RST_FIFO);

	/* set HDMI HDCP mode off: */
	reg_write(priv, REG_TBG_CNTRL_1, TBG_CNTRL_1_DWIN_DIS);
	reg_clear(priv, REG_TX33, TX33_HDMI);
	reg_write(priv, REG_ENC_CNTRL, ENC_CNTRL_CTL_CODE(0));

	/* no pre-filter or interpolator: */
	reg_write(priv, REG_HVF_CNTRL_0, HVF_CNTRL_0_PREFIL(0) |
			HVF_CNTRL_0_INTPOL(0));
	reg_set(priv, REG_FEAT_POWERDOWN, FEAT_POWERDOWN_PREFILT);
	reg_write(priv, REG_VIP_CNTRL_5, VIP_CNTRL_5_SP_CNT(0));
	reg_write(priv, REG_VIP_CNTRL_4, VIP_CNTRL_4_BLANKIT(0) |
			VIP_CNTRL_4_BLC(0));

	reg_clear(priv, REG_PLL_SERIAL_1, PLL_SERIAL_1_SRL_MAN_IZ);
	reg_clear(priv, REG_PLL_SERIAL_3, PLL_SERIAL_3_SRL_CCIR |
					  PLL_SERIAL_3_SRL_DE);
	reg_write(priv, REG_SERIALIZER, 0);
	reg_write(priv, REG_HVF_CNTRL_1, HVF_CNTRL_1_VQR(0));

	/* TODO enable pixel repeat for pixel rates less than 25Msamp/s */
	rep = 0;
	reg_write(priv, REG_RPT_CNTRL, 0);
	reg_write(priv, REG_SEL_CLK, SEL_CLK_SEL_VRF_CLK(0) |
			SEL_CLK_SEL_CLK1 | SEL_CLK_ENA_SC_CLK);

	reg_write(priv, REG_PLL_SERIAL_2, PLL_SERIAL_2_SRL_NOSC(div) |
			PLL_SERIAL_2_SRL_PR(rep));

	/* set color matrix bypass flag: */
	reg_write(priv, REG_MAT_CONTRL, MAT_CONTRL_MAT_BP |
				MAT_CONTRL_MAT_SC(1));
	reg_set(priv, REG_FEAT_POWERDOWN, FEAT_POWERDOWN_CSC);

	/* set BIAS tmds value: */
	reg_write(priv, REG_ANA_GENERAL, 0x09);

	/*
	 * Sync on rising HSYNC/VSYNC
	 */
	reg = VIP_CNTRL_3_SYNC_HS;

	/*
	 * TDA19988 requires high-active sync at input stage,
	 * so invert low-active sync provided by master encoder here
	 */
	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		reg |= VIP_CNTRL_3_H_TGL;
	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		reg |= VIP_CNTRL_3_V_TGL;
	reg_write(priv, REG_VIP_CNTRL_3, reg);

	reg_write(priv, REG_VIDFORMAT, 0x00);
	reg_write16(priv, REG_REFPIX_MSB, ref_pix);
	reg_write16(priv, REG_REFLINE_MSB, ref_line);
	reg_write16(priv, REG_NPIX_MSB, n_pix);
	reg_write16(priv, REG_NLINE_MSB, n_line);
	reg_write16(priv, REG_VS_LINE_STRT_1_MSB, vs1_line_s);
	reg_write16(priv, REG_VS_PIX_STRT_1_MSB, vs1_pix_s);
	reg_write16(priv, REG_VS_LINE_END_1_MSB, vs1_line_e);
	reg_write16(priv, REG_VS_PIX_END_1_MSB, vs1_pix_e);
	reg_write16(priv, REG_VS_LINE_STRT_2_MSB, vs2_line_s);
	reg_write16(priv, REG_VS_PIX_STRT_2_MSB, vs2_pix_s);
	reg_write16(priv, REG_VS_LINE_END_2_MSB, vs2_line_e);
	reg_write16(priv, REG_VS_PIX_END_2_MSB, vs2_pix_e);
	reg_write16(priv, REG_HS_PIX_START_MSB, hs_pix_s);
	reg_write16(priv, REG_HS_PIX_STOP_MSB, hs_pix_e);
	reg_write16(priv, REG_VWIN_START_1_MSB, vwin1_line_s);
	reg_write16(priv, REG_VWIN_END_1_MSB, vwin1_line_e);
	reg_write16(priv, REG_VWIN_START_2_MSB, vwin2_line_s);
	reg_write16(priv, REG_VWIN_END_2_MSB, vwin2_line_e);
	reg_write16(priv, REG_DE_START_MSB, de_pix_s);
	reg_write16(priv, REG_DE_STOP_MSB, de_pix_e);

	if (priv->rev == TDA19988) {
		/* let incoming pixels fill the active space (if any) */
		reg_write(priv, REG_ENABLE_SPACE, 0x00);
	}

	/*
	 * Always generate sync polarity relative to input sync and
	 * revert input stage toggled sync at output stage
	 */
	reg = TBG_CNTRL_1_DWIN_DIS | TBG_CNTRL_1_TGL_EN;
	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		reg |= TBG_CNTRL_1_H_TGL;
	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		reg |= TBG_CNTRL_1_V_TGL;
	reg_write(priv, REG_TBG_CNTRL_1, reg);

	/* must be last register set: */
	reg_write(priv, REG_TBG_CNTRL_0, 0);

	priv->tmds_clock = adjusted_mode->clock;

	/* CEA-861B section 6 says that:
	 * CEA version 1 (CEA-861) has no support for infoframes.
	 * CEA version 2 (CEA-861A) supports version 1 AVI infoframes,
	 * and optional basic audio.
	 * CEA version 3 (CEA-861B) supports version 1 and 2 AVI infoframes,
	 * and optional digital audio, with audio infoframes.
	 *
	 * Since we only support generation of version 2 AVI infoframes,
	 * ignore CEA version 2 and below (iow, behave as if we're a
	 * CEA-861 source.)
	 */
	priv->supports_infoframes = priv->connector.display_info.cea_rev >= 3;

	if (priv->supports_infoframes) {
		/* We need to turn HDMI HDCP stuff on to get audio through */
		reg &= ~TBG_CNTRL_1_DWIN_DIS;
		reg_write(priv, REG_TBG_CNTRL_1, reg);
		reg_write(priv, REG_ENC_CNTRL, ENC_CNTRL_CTL_CODE(1));
		reg_set(priv, REG_TX33, TX33_HDMI);

		tda998x_write_avi(priv, adjusted_mode);

		if (priv->audio_params.format != AFMT_UNUSED &&
		    priv->sink_has_audio)
			tda998x_configure_audio(priv, &priv->audio_params);
	}

	mutex_unlock(&priv->audio_mutex);
}
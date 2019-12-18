#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  colorspace; } ;
union hdmi_infoframe {TYPE_1__ avi; } ;
typedef  int /*<<< orphan*/  u8 ;
struct sii8620 {scalar_t__ use_packed_pixel; } ;
struct mhl3_infoframe {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BIT_PKT_FILTER_0_DROP_AVI_PKT ; 
 int BIT_PKT_FILTER_0_DROP_CEA_GAMUT_PKT ; 
 int BIT_PKT_FILTER_0_DROP_GCP_PKT ; 
 int BIT_PKT_FILTER_0_DROP_MPEG_PKT ; 
 int BIT_PKT_FILTER_1_DROP_GEN_PKT ; 
 int BIT_PKT_FILTER_1_DROP_VSIF_PKT ; 
 int BIT_PKT_FILTER_1_VSI_OVERRIDE_DIS ; 
 int BIT_TPI_INFO_FSEL_EN ; 
 int BIT_TPI_INFO_FSEL_RPT ; 
 int BIT_TPI_SC_TPI_OUTPUT_MODE_0_HDMI ; 
 int /*<<< orphan*/  HDMI_COLORSPACE_YUV422 ; 
 int /*<<< orphan*/  REG_PKT_FILTER_0 ; 
 int /*<<< orphan*/  REG_TPI_AVI_CHSUM ; 
 int /*<<< orphan*/  REG_TPI_INFO_B0 ; 
 int /*<<< orphan*/  REG_TPI_INFO_FSEL ; 
 int /*<<< orphan*/  REG_TPI_SC ; 
 int VAL_TPI_INFO_FSEL_VSI ; 
 int drm_hdmi_avi_infoframe_from_display_mode (TYPE_1__*,int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 int hdmi_avi_infoframe_pack (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mhl3_infoframe_init (struct mhl3_infoframe*) ; 
 int mhl3_infoframe_pack (struct mhl3_infoframe*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_is_mhl3 (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  sii8620_write_buf (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sii8620_set_infoframes(struct sii8620 *ctx,
				   struct drm_display_mode *mode)
{
	struct mhl3_infoframe mhl_frm;
	union hdmi_infoframe frm;
	u8 buf[31];
	int ret;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frm.avi,
						       NULL, mode);
	if (ctx->use_packed_pixel)
		frm.avi.colorspace = HDMI_COLORSPACE_YUV422;

	if (!ret)
		ret = hdmi_avi_infoframe_pack(&frm.avi, buf, ARRAY_SIZE(buf));
	if (ret > 0)
		sii8620_write_buf(ctx, REG_TPI_AVI_CHSUM, buf + 3, ret - 3);

	if (!sii8620_is_mhl3(ctx) || !ctx->use_packed_pixel) {
		sii8620_write(ctx, REG_TPI_SC,
			BIT_TPI_SC_TPI_OUTPUT_MODE_0_HDMI);
		sii8620_write(ctx, REG_PKT_FILTER_0,
			BIT_PKT_FILTER_0_DROP_CEA_GAMUT_PKT |
			BIT_PKT_FILTER_0_DROP_MPEG_PKT |
			BIT_PKT_FILTER_0_DROP_GCP_PKT,
			BIT_PKT_FILTER_1_DROP_GEN_PKT);
		return;
	}

	sii8620_write(ctx, REG_PKT_FILTER_0,
		BIT_PKT_FILTER_0_DROP_CEA_GAMUT_PKT |
		BIT_PKT_FILTER_0_DROP_MPEG_PKT |
		BIT_PKT_FILTER_0_DROP_AVI_PKT |
		BIT_PKT_FILTER_0_DROP_GCP_PKT,
		BIT_PKT_FILTER_1_VSI_OVERRIDE_DIS |
		BIT_PKT_FILTER_1_DROP_GEN_PKT |
		BIT_PKT_FILTER_1_DROP_VSIF_PKT);

	sii8620_write(ctx, REG_TPI_INFO_FSEL, BIT_TPI_INFO_FSEL_EN
		| BIT_TPI_INFO_FSEL_RPT | VAL_TPI_INFO_FSEL_VSI);
	ret = mhl3_infoframe_init(&mhl_frm);
	if (!ret)
		ret = mhl3_infoframe_pack(&mhl_frm, buf, ARRAY_SIZE(buf));
	sii8620_write_buf(ctx, REG_TPI_INFO_B0, buf, ret);
}
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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mtk_hdmi {int /*<<< orphan*/  dev; } ;
typedef  enum hdmi_infoframe_type { ____Placeholder_hdmi_infoframe_type } hdmi_infoframe_type ;

/* Variables and functions */
 int CTRL_AUDIO_EN ; 
 int CTRL_AVI_EN ; 
 int CTRL_SPD_EN ; 
 int /*<<< orphan*/  GRL_ACP_ISRC_CTRL ; 
 int /*<<< orphan*/  GRL_CTRL ; 
 int /*<<< orphan*/  GRL_IFM_PORT ; 
 int /*<<< orphan*/  GRL_INFOFRM_LNG ; 
 int /*<<< orphan*/  GRL_INFOFRM_TYPE ; 
 int /*<<< orphan*/  GRL_INFOFRM_VER ; 
#define  HDMI_INFOFRAME_TYPE_AUDIO 131 
#define  HDMI_INFOFRAME_TYPE_AVI 130 
#define  HDMI_INFOFRAME_TYPE_SPD 129 
#define  HDMI_INFOFRAME_TYPE_VENDOR 128 
 int VS_EN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtk_hdmi_clear_bits (struct mtk_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_hdmi_set_bits (struct mtk_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_hdmi_write (struct mtk_hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mtk_hdmi_hw_send_info_frame(struct mtk_hdmi *hdmi, u8 *buffer,
					u8 len)
{
	u32 ctrl_reg = GRL_CTRL;
	int i;
	u8 *frame_data;
	enum hdmi_infoframe_type frame_type;
	u8 frame_ver;
	u8 frame_len;
	u8 checksum;
	int ctrl_frame_en = 0;

	frame_type = *buffer;
	buffer += 1;
	frame_ver = *buffer;
	buffer += 1;
	frame_len = *buffer;
	buffer += 1;
	checksum = *buffer;
	buffer += 1;
	frame_data = buffer;

	dev_dbg(hdmi->dev,
		"frame_type:0x%x,frame_ver:0x%x,frame_len:0x%x,checksum:0x%x\n",
		frame_type, frame_ver, frame_len, checksum);

	switch (frame_type) {
	case HDMI_INFOFRAME_TYPE_AVI:
		ctrl_frame_en = CTRL_AVI_EN;
		ctrl_reg = GRL_CTRL;
		break;
	case HDMI_INFOFRAME_TYPE_SPD:
		ctrl_frame_en = CTRL_SPD_EN;
		ctrl_reg = GRL_CTRL;
		break;
	case HDMI_INFOFRAME_TYPE_AUDIO:
		ctrl_frame_en = CTRL_AUDIO_EN;
		ctrl_reg = GRL_CTRL;
		break;
	case HDMI_INFOFRAME_TYPE_VENDOR:
		ctrl_frame_en = VS_EN;
		ctrl_reg = GRL_ACP_ISRC_CTRL;
		break;
	default:
		dev_err(hdmi->dev, "Unknown infoframe type %d\n", frame_type);
		return;
	}
	mtk_hdmi_clear_bits(hdmi, ctrl_reg, ctrl_frame_en);
	mtk_hdmi_write(hdmi, GRL_INFOFRM_TYPE, frame_type);
	mtk_hdmi_write(hdmi, GRL_INFOFRM_VER, frame_ver);
	mtk_hdmi_write(hdmi, GRL_INFOFRM_LNG, frame_len);

	mtk_hdmi_write(hdmi, GRL_IFM_PORT, checksum);
	for (i = 0; i < frame_len; i++)
		mtk_hdmi_write(hdmi, GRL_IFM_PORT, frame_data[i]);

	mtk_hdmi_set_bits(hdmi, ctrl_reg, ctrl_frame_en);
}
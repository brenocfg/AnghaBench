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
typedef  size_t u8 ;
struct v4l2_subdev {int dummy; } ;
struct m5mols_scenemode {size_t metering; size_t ev_bias; size_t wb_mode; size_t wb_preset; size_t chroma_en; size_t chroma_lvl; size_t edge_en; size_t edge_lvl; size_t af_range; size_t fd_mode; size_t tone; size_t iso; size_t wdr; size_t mcc; size_t light; size_t flash; size_t capt_mode; } ;
struct m5mols_info {int /*<<< orphan*/  lock_3a; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_EV_PRESET_CAPTURE ; 
 int /*<<< orphan*/  AE_EV_PRESET_MONITOR ; 
 int /*<<< orphan*/  AE_INDEX ; 
 int /*<<< orphan*/  AE_ISO ; 
 int /*<<< orphan*/  AE_MODE ; 
 int /*<<< orphan*/  AF_MODE ; 
 int /*<<< orphan*/  AWB_MANUAL ; 
 int /*<<< orphan*/  AWB_MODE ; 
 int /*<<< orphan*/  CAPC_MODE ; 
 int /*<<< orphan*/  CAPP_FLASH_CTRL ; 
 int /*<<< orphan*/  CAPP_LIGHT_CTRL ; 
 int /*<<< orphan*/  CAPP_MCC_MODE ; 
 int /*<<< orphan*/  CAPP_WDR_EN ; 
 int EINVAL ; 
 int /*<<< orphan*/  FD_CTL ; 
 int /*<<< orphan*/  MON_CHROMA_EN ; 
 int /*<<< orphan*/  MON_CHROMA_LVL ; 
 int /*<<< orphan*/  MON_EDGE_EN ; 
 int /*<<< orphan*/  MON_EDGE_LVL ; 
 int /*<<< orphan*/  MON_TONE_CTL ; 
 int /*<<< orphan*/  REG_CAPTURE ; 
 int /*<<< orphan*/  REG_MONITOR ; 
 size_t REG_SCENE_CANDLE ; 
 scalar_t__ is_available_af (struct m5mols_info*) ; 
 struct m5mols_scenemode* m5mols_default_scenemode ; 
 int m5mols_set_mode (struct m5mols_info*,int /*<<< orphan*/ ) ; 
 int m5mols_write (struct v4l2_subdev*,int /*<<< orphan*/ ,size_t) ; 
 int v4l2_ctrl_s_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int m5mols_do_scenemode(struct m5mols_info *info, u8 mode)
{
	struct v4l2_subdev *sd = &info->sd;
	struct m5mols_scenemode scenemode = m5mols_default_scenemode[mode];
	int ret;

	if (mode > REG_SCENE_CANDLE)
		return -EINVAL;

	ret = v4l2_ctrl_s_ctrl(info->lock_3a, 0);
	if (!ret)
		ret = m5mols_write(sd, AE_EV_PRESET_MONITOR, mode);
	if (!ret)
		ret = m5mols_write(sd, AE_EV_PRESET_CAPTURE, mode);
	if (!ret)
		ret = m5mols_write(sd, AE_MODE, scenemode.metering);
	if (!ret)
		ret = m5mols_write(sd, AE_INDEX, scenemode.ev_bias);
	if (!ret)
		ret = m5mols_write(sd, AWB_MODE, scenemode.wb_mode);
	if (!ret)
		ret = m5mols_write(sd, AWB_MANUAL, scenemode.wb_preset);
	if (!ret)
		ret = m5mols_write(sd, MON_CHROMA_EN, scenemode.chroma_en);
	if (!ret)
		ret = m5mols_write(sd, MON_CHROMA_LVL, scenemode.chroma_lvl);
	if (!ret)
		ret = m5mols_write(sd, MON_EDGE_EN, scenemode.edge_en);
	if (!ret)
		ret = m5mols_write(sd, MON_EDGE_LVL, scenemode.edge_lvl);
	if (!ret && is_available_af(info))
		ret = m5mols_write(sd, AF_MODE, scenemode.af_range);
	if (!ret && is_available_af(info))
		ret = m5mols_write(sd, FD_CTL, scenemode.fd_mode);
	if (!ret)
		ret = m5mols_write(sd, MON_TONE_CTL, scenemode.tone);
	if (!ret)
		ret = m5mols_write(sd, AE_ISO, scenemode.iso);
	if (!ret)
		ret = m5mols_set_mode(info, REG_CAPTURE);
	if (!ret)
		ret = m5mols_write(sd, CAPP_WDR_EN, scenemode.wdr);
	if (!ret)
		ret = m5mols_write(sd, CAPP_MCC_MODE, scenemode.mcc);
	if (!ret)
		ret = m5mols_write(sd, CAPP_LIGHT_CTRL, scenemode.light);
	if (!ret)
		ret = m5mols_write(sd, CAPP_FLASH_CTRL, scenemode.flash);
	if (!ret)
		ret = m5mols_write(sd, CAPC_MODE, scenemode.capt_mode);
	if (!ret)
		ret = m5mols_set_mode(info, REG_MONITOR);

	return ret;
}
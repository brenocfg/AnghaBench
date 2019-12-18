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
struct wdt87xx_sys_param {int vendor_id; int product_id; int xmls_id1; int xmls_id2; int phy_ch_x; int phy_ch_y; int phy_w; int phy_h; int scaling_factor; int max_x; int plat_id; int fw_id; int /*<<< orphan*/  max_y; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTL_PARAM_OFFSET_FACTOR ; 
 int CTL_PARAM_OFFSET_PHY_CH_X ; 
 int CTL_PARAM_OFFSET_PHY_CH_Y ; 
 int CTL_PARAM_OFFSET_PHY_H ; 
 int CTL_PARAM_OFFSET_PHY_W ; 
 int CTL_PARAM_OFFSET_XMLS_ID1 ; 
 int CTL_PARAM_OFFSET_XMLS_ID2 ; 
 int DEV_DESC_OFFSET_PID ; 
 int DEV_DESC_OFFSET_VID ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int,int) ; 
 int EINVAL ; 
 int MAX_UNIT_AXIS ; 
 int PKT_READ_SIZE ; 
 int /*<<< orphan*/  STRIDX_PARAMETERS ; 
 int /*<<< orphan*/  STRIDX_PLATFORM_ID ; 
 int /*<<< orphan*/  WDT_GD_DEVICE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 int get_unaligned_le16 (int*) ; 
 int wdt87xx_get_desc (struct i2c_client*,int /*<<< orphan*/ ,int*,int) ; 
 int wdt87xx_get_feature (struct i2c_client*,int*,int) ; 
 int wdt87xx_get_string (struct i2c_client*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int wdt87xx_get_sysparam(struct i2c_client *client,
				struct wdt87xx_sys_param *param)
{
	u8 buf[PKT_READ_SIZE];
	int error;

	error = wdt87xx_get_desc(client, WDT_GD_DEVICE, buf, 18);
	if (error) {
		dev_err(&client->dev, "failed to get device desc\n");
		return error;
	}

	param->vendor_id = get_unaligned_le16(buf + DEV_DESC_OFFSET_VID);
	param->product_id = get_unaligned_le16(buf + DEV_DESC_OFFSET_PID);

	error = wdt87xx_get_string(client, STRIDX_PARAMETERS, buf, 34);
	if (error) {
		dev_err(&client->dev, "failed to get parameters\n");
		return error;
	}

	param->xmls_id1 = get_unaligned_le16(buf + CTL_PARAM_OFFSET_XMLS_ID1);
	param->xmls_id2 = get_unaligned_le16(buf + CTL_PARAM_OFFSET_XMLS_ID2);
	param->phy_ch_x = get_unaligned_le16(buf + CTL_PARAM_OFFSET_PHY_CH_X);
	param->phy_ch_y = get_unaligned_le16(buf + CTL_PARAM_OFFSET_PHY_CH_Y);
	param->phy_w = get_unaligned_le16(buf + CTL_PARAM_OFFSET_PHY_W) / 10;
	param->phy_h = get_unaligned_le16(buf + CTL_PARAM_OFFSET_PHY_H) / 10;

	/* Get the scaling factor of pixel to logical coordinate */
	param->scaling_factor =
			get_unaligned_le16(buf + CTL_PARAM_OFFSET_FACTOR);

	param->max_x = MAX_UNIT_AXIS;
	param->max_y = DIV_ROUND_CLOSEST(MAX_UNIT_AXIS * param->phy_h,
					 param->phy_w);

	error = wdt87xx_get_string(client, STRIDX_PLATFORM_ID, buf, 8);
	if (error) {
		dev_err(&client->dev, "failed to get platform id\n");
		return error;
	}

	param->plat_id = buf[1];

	buf[0] = 0xf2;
	error = wdt87xx_get_feature(client, buf, 16);
	if (error) {
		dev_err(&client->dev, "failed to get firmware id\n");
		return error;
	}

	if (buf[0] != 0xf2) {
		dev_err(&client->dev, "wrong id of fw response: 0x%x\n",
			buf[0]);
		return -EINVAL;
	}

	param->fw_id = get_unaligned_le16(&buf[1]);

	dev_info(&client->dev,
		 "fw_id: 0x%x, plat_id: 0x%x, xml_id1: %04x, xml_id2: %04x\n",
		 param->fw_id, param->plat_id,
		 param->xmls_id1, param->xmls_id2);

	return 0;
}
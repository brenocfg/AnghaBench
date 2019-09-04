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
struct v4l2_subdev {int dummy; } ;
struct ths7303_state {struct ths7303_platform_data* pdata; } ;
struct ths7303_platform_data {int ch_1; int ch_2; int ch_3; } ;
struct i2c_client {int dummy; } ;
typedef  enum ths7303_filter_mode { ____Placeholder_ths7303_filter_mode } ths7303_filter_mode ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  THS7303_CHANNEL_1 ; 
 int /*<<< orphan*/  THS7303_CHANNEL_2 ; 
 int /*<<< orphan*/  THS7303_CHANNEL_3 ; 
#define  THS7303_FILTER_MODE_1080P 131 
#define  THS7303_FILTER_MODE_480I_576I 130 
#define  THS7303_FILTER_MODE_480P_576P 129 
#define  THS7303_FILTER_MODE_720P_1080I 128 
 int /*<<< orphan*/  pr_info (char*) ; 
 int ths7303_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct ths7303_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ths7303_setval(struct v4l2_subdev *sd,
			  enum ths7303_filter_mode mode)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ths7303_state *state = to_state(sd);
	const struct ths7303_platform_data *pdata = state->pdata;
	u8 val, sel = 0;
	int err, disable = 0;

	if (!client)
		return -EINVAL;

	switch (mode) {
	case THS7303_FILTER_MODE_1080P:
		sel = 0x3;	/*1080p and SXGA/UXGA */
		break;
	case THS7303_FILTER_MODE_720P_1080I:
		sel = 0x2;	/*720p, 1080i and SVGA/XGA */
		break;
	case THS7303_FILTER_MODE_480P_576P:
		sel = 0x1;	/* EDTV 480p/576p and VGA */
		break;
	case THS7303_FILTER_MODE_480I_576I:
		sel = 0x0;	/* SDTV, S-Video, 480i/576i */
		break;
	default:
		/* disable all channels */
		disable = 1;
	}

	val = (sel << 6) | (sel << 3);
	if (!disable)
		val |= (pdata->ch_1 & 0x27);
	err = ths7303_write(sd, THS7303_CHANNEL_1, val);
	if (err)
		goto out;

	val = (sel << 6) | (sel << 3);
	if (!disable)
		val |= (pdata->ch_2 & 0x27);
	err = ths7303_write(sd, THS7303_CHANNEL_2, val);
	if (err)
		goto out;

	val = (sel << 6) | (sel << 3);
	if (!disable)
		val |= (pdata->ch_3 & 0x27);
	err = ths7303_write(sd, THS7303_CHANNEL_3, val);
	if (err)
		goto out;

	return 0;
out:
	pr_info("write byte data failed\n");
	return err;
}
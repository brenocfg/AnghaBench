#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct mt9m111 {scalar_t__ pclk_sample; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  output_fmt_ctrl2; } ;
struct TYPE_3__ {int /*<<< orphan*/  output_fmt_ctrl2; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MEDIA_BUS_FMT_BGR565_2X8_BE 139 
#define  MEDIA_BUS_FMT_BGR565_2X8_LE 138 
#define  MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE 137 
#define  MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE 136 
#define  MEDIA_BUS_FMT_RGB565_2X8_BE 135 
#define  MEDIA_BUS_FMT_RGB565_2X8_LE 134 
#define  MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE 133 
#define  MEDIA_BUS_FMT_SBGGR8_1X8 132 
#define  MEDIA_BUS_FMT_UYVY8_2X8 131 
#define  MEDIA_BUS_FMT_VYUY8_2X8 130 
#define  MEDIA_BUS_FMT_YUYV8_2X8 129 
#define  MEDIA_BUS_FMT_YVYU8_2X8 128 
 int MT9M111_OUTFMT_BYPASS_IFP ; 
 int MT9M111_OUTFMT_INV_PIX_CLOCK ; 
 int MT9M111_OUTFMT_PROCESSED_BAYER ; 
 int MT9M111_OUTFMT_RGB ; 
 int MT9M111_OUTFMT_RGB444x ; 
 int MT9M111_OUTFMT_RGB555 ; 
 int MT9M111_OUTFMT_RGB565 ; 
 int MT9M111_OUTFMT_RGBx444 ; 
 int MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN ; 
 int MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B ; 
 TYPE_2__ context_a ; 
 TYPE_1__ context_b ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mt9m111_reg_mask (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m111_set_pixfmt(struct mt9m111 *mt9m111,
			      u32 code)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	u16 data_outfmt2, mask_outfmt2 = MT9M111_OUTFMT_PROCESSED_BAYER |
		MT9M111_OUTFMT_BYPASS_IFP | MT9M111_OUTFMT_RGB |
		MT9M111_OUTFMT_RGB565 | MT9M111_OUTFMT_RGB555 |
		MT9M111_OUTFMT_RGB444x | MT9M111_OUTFMT_RGBx444 |
		MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN |
		MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B;
	int ret;

	switch (code) {
	case MEDIA_BUS_FMT_SBGGR8_1X8:
		data_outfmt2 = MT9M111_OUTFMT_PROCESSED_BAYER |
			MT9M111_OUTFMT_RGB;
		break;
	case MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE:
		data_outfmt2 = MT9M111_OUTFMT_BYPASS_IFP | MT9M111_OUTFMT_RGB;
		break;
	case MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB555 |
			MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN;
		break;
	case MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB555;
		break;
	case MEDIA_BUS_FMT_RGB565_2X8_LE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB565 |
			MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN;
		break;
	case MEDIA_BUS_FMT_RGB565_2X8_BE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB565;
		break;
	case MEDIA_BUS_FMT_BGR565_2X8_BE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB565 |
			MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B;
		break;
	case MEDIA_BUS_FMT_BGR565_2X8_LE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB565 |
			MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN |
			MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B;
		break;
	case MEDIA_BUS_FMT_UYVY8_2X8:
		data_outfmt2 = 0;
		break;
	case MEDIA_BUS_FMT_VYUY8_2X8:
		data_outfmt2 = MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B;
		break;
	case MEDIA_BUS_FMT_YUYV8_2X8:
		data_outfmt2 = MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN;
		break;
	case MEDIA_BUS_FMT_YVYU8_2X8:
		data_outfmt2 = MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN |
			MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B;
		break;
	default:
		dev_err(&client->dev, "Pixel format not handled: %x\n", code);
		return -EINVAL;
	}

	/* receiver samples on falling edge, chip-hw default is rising */
	if (mt9m111->pclk_sample == 0)
		mask_outfmt2 |= MT9M111_OUTFMT_INV_PIX_CLOCK;

	ret = mt9m111_reg_mask(client, context_a.output_fmt_ctrl2,
			       data_outfmt2, mask_outfmt2);
	if (!ret)
		ret = mt9m111_reg_mask(client, context_b.output_fmt_ctrl2,
				       data_outfmt2, mask_outfmt2);

	return ret;
}
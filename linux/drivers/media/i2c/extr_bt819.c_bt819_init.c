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
struct v4l2_subdev {int dummy; } ;
struct timing {int vdelay; int vactive; int hdelay; int hactive; int hscale; } ;
struct bt819 {int norm; } ;
typedef  int /*<<< orphan*/  init ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  bt819_write (struct bt819*,int,int) ; 
 int bt819_write_block (struct bt819*,unsigned char*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct timing* timing_data ; 
 struct bt819* to_bt819 (struct v4l2_subdev*) ; 

__attribute__((used)) static int bt819_init(struct v4l2_subdev *sd)
{
	static unsigned char init[] = {
		/*0x1f, 0x00,*/     /* Reset */
		0x01, 0x59,	/* 0x01 input format */
		0x02, 0x00,	/* 0x02 temporal decimation */
		0x03, 0x12,	/* 0x03 Cropping msb */
		0x04, 0x16,	/* 0x04 Vertical Delay, lsb */
		0x05, 0xe0,	/* 0x05 Vertical Active lsb */
		0x06, 0x80,	/* 0x06 Horizontal Delay lsb */
		0x07, 0xd0,	/* 0x07 Horizontal Active lsb */
		0x08, 0x00,	/* 0x08 Horizontal Scaling msb */
		0x09, 0xf8,	/* 0x09 Horizontal Scaling lsb */
		0x0a, 0x00,	/* 0x0a Brightness control */
		0x0b, 0x30,	/* 0x0b Miscellaneous control */
		0x0c, 0xd8,	/* 0x0c Luma Gain lsb */
		0x0d, 0xfe,	/* 0x0d Chroma Gain (U) lsb */
		0x0e, 0xb4,	/* 0x0e Chroma Gain (V) msb */
		0x0f, 0x00,	/* 0x0f Hue control */
		0x12, 0x04,	/* 0x12 Output Format */
		0x13, 0x20,	/* 0x13 Vertical Scaling msb 0x00
					   chroma comb OFF, line drop scaling, interlace scaling
					   BUG? Why does turning the chroma comb on fuck up color?
					   Bug in the bt819 stepping on my board?
					*/
		0x14, 0x00,	/* 0x14 Vertical Scaling lsb */
		0x16, 0x07,	/* 0x16 Video Timing Polarity
					   ACTIVE=active low
					   FIELD: high=odd,
					   vreset=active high,
					   hreset=active high */
		0x18, 0x68,	/* 0x18 AGC Delay */
		0x19, 0x5d,	/* 0x19 Burst Gate Delay */
		0x1a, 0x80,	/* 0x1a ADC Interface */
	};

	struct bt819 *decoder = to_bt819(sd);
	struct timing *timing = &timing_data[(decoder->norm & V4L2_STD_525_60) ? 1 : 0];

	init[0x03 * 2 - 1] =
	    (((timing->vdelay >> 8) & 0x03) << 6) |
	    (((timing->vactive >> 8) & 0x03) << 4) |
	    (((timing->hdelay >> 8) & 0x03) << 2) |
	    ((timing->hactive >> 8) & 0x03);
	init[0x04 * 2 - 1] = timing->vdelay & 0xff;
	init[0x05 * 2 - 1] = timing->vactive & 0xff;
	init[0x06 * 2 - 1] = timing->hdelay & 0xff;
	init[0x07 * 2 - 1] = timing->hactive & 0xff;
	init[0x08 * 2 - 1] = timing->hscale >> 8;
	init[0x09 * 2 - 1] = timing->hscale & 0xff;
	/* 0x15 in array is address 0x19 */
	init[0x15 * 2 - 1] = (decoder->norm & V4L2_STD_625_50) ? 115 : 93;	/* Chroma burst delay */
	/* reset */
	bt819_write(decoder, 0x1f, 0x00);
	mdelay(1);

	/* init */
	return bt819_write_block(decoder, init, sizeof(init));
}
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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct tvp5150 {int /*<<< orphan*/  hdl; scalar_t__ irq; struct regmap* regmap; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVP5150_CONF_SHARED_PIN ; 
 int /*<<< orphan*/  TVP5150_INTT_CONFIG_REG_B ; 
 int /*<<< orphan*/  TVP5150_INT_CONF ; 
 int TVP5150_VDPOE ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_init_default ; 
 int /*<<< orphan*/  tvp5150_selmux (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_vdp_init (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_write_inittab (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tvp5150_reset(struct v4l2_subdev *sd, u32 val)
{
	struct tvp5150 *decoder = to_tvp5150(sd);
	struct regmap *map = decoder->regmap;

	/* Initializes TVP5150 to its default values */
	tvp5150_write_inittab(sd, tvp5150_init_default);

	if (decoder->irq) {
		/* Configure pins: FID, VSYNC, INTREQ, SCLK */
		regmap_write(map, TVP5150_CONF_SHARED_PIN, 0x0);
		/* Set interrupt polarity to active high */
		regmap_write(map, TVP5150_INT_CONF, TVP5150_VDPOE | 0x1);
		regmap_write(map, TVP5150_INTT_CONFIG_REG_B, 0x1);
	} else {
		/* Configure pins: FID, VSYNC, GPCL/VBLK, SCLK */
		regmap_write(map, TVP5150_CONF_SHARED_PIN, 0x2);
		/* Keep interrupt polarity active low */
		regmap_write(map, TVP5150_INT_CONF, TVP5150_VDPOE);
		regmap_write(map, TVP5150_INTT_CONFIG_REG_B, 0x0);
	}

	/* Initializes VDP registers */
	tvp5150_vdp_init(sd);

	/* Selects decoder input */
	tvp5150_selmux(sd);

	/* Initialize image preferences */
	v4l2_ctrl_handler_setup(&decoder->hdl);

	return 0;
}
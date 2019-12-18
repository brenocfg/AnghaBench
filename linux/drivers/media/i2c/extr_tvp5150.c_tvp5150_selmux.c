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
struct v4l2_subdev {int /*<<< orphan*/  dev; } ;
struct tvp5150 {int dev_id; int rom_ver; int input; int /*<<< orphan*/  regmap; int /*<<< orphan*/  output; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
#define  TVP5150_COMPOSITE0 130 
#define  TVP5150_COMPOSITE1 129 
 int /*<<< orphan*/  TVP5150_MISC_CTL ; 
 unsigned int TVP5150_MISC_CTL_GPCL ; 
 unsigned int TVP5150_MISC_CTL_HVLK ; 
 int /*<<< orphan*/  TVP5150_OP_MODE_CTL ; 
#define  TVP5150_SVIDEO 128 
 int /*<<< orphan*/  TVP5150_VD_IN_SRC_SEL_1 ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 

__attribute__((used)) static void tvp5150_selmux(struct v4l2_subdev *sd)
{
	int opmode = 0;
	struct tvp5150 *decoder = to_tvp5150(sd);
	unsigned int mask, val;
	int input = 0;

	/* Only tvp5150am1 and tvp5151 have signal generator support */
	if ((decoder->dev_id == 0x5150 && decoder->rom_ver == 0x0400) ||
	    (decoder->dev_id == 0x5151 && decoder->rom_ver == 0x0100)) {
		if (!decoder->enable)
			input = 8;
	}

	switch (decoder->input) {
	case TVP5150_COMPOSITE1:
		input |= 2;
		/* fall through */
	case TVP5150_COMPOSITE0:
		break;
	case TVP5150_SVIDEO:
	default:
		input |= 1;
		break;
	}

	dev_dbg_lvl(sd->dev, 1, debug, "Selecting video route: route input=%i, output=%i => tvp5150 input=%i, opmode=%i\n",
			decoder->input, decoder->output,
			input, opmode);

	regmap_write(decoder->regmap, TVP5150_OP_MODE_CTL, opmode);
	regmap_write(decoder->regmap, TVP5150_VD_IN_SRC_SEL_1, input);

	/*
	 * Setup the FID/GLCO/VLK/HVLK and INTREQ/GPCL/VBLK output signals. For
	 * S-Video we output the vertical lock (VLK) signal on FID/GLCO/VLK/HVLK
	 * and set INTREQ/GPCL/VBLK to logic 0. For composite we output the
	 * field indicator (FID) signal on FID/GLCO/VLK/HVLK and set
	 * INTREQ/GPCL/VBLK to logic 1.
	 */
	mask = TVP5150_MISC_CTL_GPCL | TVP5150_MISC_CTL_HVLK;
	if (decoder->input == TVP5150_SVIDEO)
		val = TVP5150_MISC_CTL_HVLK;
	else
		val = TVP5150_MISC_CTL_GPCL;
	regmap_update_bits(decoder->regmap, TVP5150_MISC_CTL, mask, val);
}
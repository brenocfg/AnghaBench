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
struct tvp514x_decoder {int streaming; int /*<<< orphan*/  int_seq; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  REG_OPERATION_MODE ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 int tvp514x_configure (struct v4l2_subdev*,struct tvp514x_decoder*) ; 
 int tvp514x_detect (struct v4l2_subdev*,struct tvp514x_decoder*) ; 
 int tvp514x_write_reg (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int tvp514x_write_regs (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int tvp514x_s_stream(struct v4l2_subdev *sd, int enable)
{
	int err = 0;
	struct tvp514x_decoder *decoder = to_decoder(sd);

	if (decoder->streaming == enable)
		return 0;

	switch (enable) {
	case 0:
	{
		/* Power Down Sequence */
		err = tvp514x_write_reg(sd, REG_OPERATION_MODE, 0x01);
		if (err) {
			v4l2_err(sd, "Unable to turn off decoder\n");
			return err;
		}
		decoder->streaming = enable;
		break;
	}
	case 1:
	{
		/* Power Up Sequence */
		err = tvp514x_write_regs(sd, decoder->int_seq);
		if (err) {
			v4l2_err(sd, "Unable to turn on decoder\n");
			return err;
		}
		/* Detect if not already detected */
		err = tvp514x_detect(sd, decoder);
		if (err) {
			v4l2_err(sd, "Unable to detect decoder\n");
			return err;
		}
		err = tvp514x_configure(sd, decoder);
		if (err) {
			v4l2_err(sd, "Unable to configure decoder\n");
			return err;
		}
		decoder->streaming = enable;
		break;
	}
	default:
		err = -ENODEV;
		break;
	}

	return err;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct tvp514x_decoder {scalar_t__ output; scalar_t__ input; TYPE_1__* tvp514x_regs; } ;
typedef  enum tvp514x_output { ____Placeholder_tvp514x_output } tvp514x_output ;
typedef  enum tvp514x_input { ____Placeholder_tvp514x_input } tvp514x_input ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INPUT_INVALID ; 
 scalar_t__ OUTPUT_INVALID ; 
 size_t REG_INPUT_SEL ; 
 size_t REG_OUTPUT_FORMATTER1 ; 
 int /*<<< orphan*/  debug ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 int tvp514x_read_reg (struct v4l2_subdev*,size_t) ; 
 int tvp514x_write_reg (struct v4l2_subdev*,size_t,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int tvp514x_s_routing(struct v4l2_subdev *sd,
				u32 input, u32 output, u32 config)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);
	int err;
	enum tvp514x_input input_sel;
	enum tvp514x_output output_sel;

	if ((input >= INPUT_INVALID) ||
			(output >= OUTPUT_INVALID))
		/* Index out of bound */
		return -EINVAL;

	input_sel = input;
	output_sel = output;

	err = tvp514x_write_reg(sd, REG_INPUT_SEL, input_sel);
	if (err)
		return err;

	output_sel |= tvp514x_read_reg(sd,
			REG_OUTPUT_FORMATTER1) & 0x7;
	err = tvp514x_write_reg(sd, REG_OUTPUT_FORMATTER1,
			output_sel);
	if (err)
		return err;

	decoder->tvp514x_regs[REG_INPUT_SEL].val = input_sel;
	decoder->tvp514x_regs[REG_OUTPUT_FORMATTER1].val = output_sel;
	decoder->input = input;
	decoder->output = output;

	v4l2_dbg(1, debug, sd, "Input set to: %d\n", input_sel);

	return 0;
}
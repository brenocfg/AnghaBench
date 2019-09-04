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
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct adv7183 {scalar_t__ input; scalar_t__ output; } ;

/* Variables and functions */
#define  ADV7183_16BIT_OUT 143 
#define  ADV7183_COMPONENT0 142 
#define  ADV7183_COMPONENT1 141 
#define  ADV7183_COMPOSITE1 140 
#define  ADV7183_COMPOSITE10 139 
#define  ADV7183_COMPOSITE2 138 
#define  ADV7183_COMPOSITE3 137 
#define  ADV7183_COMPOSITE4 136 
#define  ADV7183_COMPOSITE5 135 
#define  ADV7183_COMPOSITE6 134 
#define  ADV7183_COMPOSITE7 133 
#define  ADV7183_COMPOSITE8 132 
#define  ADV7183_COMPOSITE9 131 
 int /*<<< orphan*/  ADV7183_IN_CTRL ; 
 int /*<<< orphan*/  ADV7183_OUT_CTRL ; 
#define  ADV7183_SVIDEO0 130 
#define  ADV7183_SVIDEO1 129 
#define  ADV7183_SVIDEO2 128 
 int EINVAL ; 
 int adv7183_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv7183_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct adv7183* to_adv7183 (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7183_s_routing(struct v4l2_subdev *sd,
				u32 input, u32 output, u32 config)
{
	struct adv7183 *decoder = to_adv7183(sd);
	int reg;

	if ((input > ADV7183_COMPONENT1) || (output > ADV7183_16BIT_OUT))
		return -EINVAL;

	if (input != decoder->input) {
		decoder->input = input;
		reg = adv7183_read(sd, ADV7183_IN_CTRL) & 0xF0;
		switch (input) {
		case ADV7183_COMPOSITE1:
			reg |= 0x1;
			break;
		case ADV7183_COMPOSITE2:
			reg |= 0x2;
			break;
		case ADV7183_COMPOSITE3:
			reg |= 0x3;
			break;
		case ADV7183_COMPOSITE4:
			reg |= 0x4;
			break;
		case ADV7183_COMPOSITE5:
			reg |= 0x5;
			break;
		case ADV7183_COMPOSITE6:
			reg |= 0xB;
			break;
		case ADV7183_COMPOSITE7:
			reg |= 0xC;
			break;
		case ADV7183_COMPOSITE8:
			reg |= 0xD;
			break;
		case ADV7183_COMPOSITE9:
			reg |= 0xE;
			break;
		case ADV7183_COMPOSITE10:
			reg |= 0xF;
			break;
		case ADV7183_SVIDEO0:
			reg |= 0x6;
			break;
		case ADV7183_SVIDEO1:
			reg |= 0x7;
			break;
		case ADV7183_SVIDEO2:
			reg |= 0x8;
			break;
		case ADV7183_COMPONENT0:
			reg |= 0x9;
			break;
		case ADV7183_COMPONENT1:
			reg |= 0xA;
			break;
		default:
			break;
		}
		adv7183_write(sd, ADV7183_IN_CTRL, reg);
	}

	if (output != decoder->output) {
		decoder->output = output;
		reg = adv7183_read(sd, ADV7183_OUT_CTRL) & 0xC0;
		switch (output) {
		case ADV7183_16BIT_OUT:
			reg |= 0x9;
			break;
		default:
			reg |= 0xC;
			break;
		}
		adv7183_write(sd, ADV7183_OUT_CTRL, reg);
	}

	return 0;
}
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
typedef  int v4l2_std_id ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct adv7393_std_info {int stdid; int standard_val3; int fsc_val; } ;
struct adv7393_state {int reg80; int reg01; int reg82; } ;

/* Variables and functions */
 scalar_t__ ADV7393_FSC_REG0 ; 
 scalar_t__ ADV7393_FSC_REG3 ; 
 scalar_t__ ADV7393_MODE_SELECT_REG ; 
 scalar_t__ ADV7393_SD_MODE_REG1 ; 
 scalar_t__ ADV7393_SD_MODE_REG2 ; 
 int ARRAY_SIZE (struct adv7393_std_info*) ; 
 int EINVAL ; 
 int INPUT_MODE_MASK ; 
 int SD_INPUT_MODE ; 
 int SD_PEDESTAL_DI ; 
 int SD_PEDESTAL_EN ; 
 int SD_STD_MASK ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_NTSC_443 ; 
 int adv7393_write (struct v4l2_subdev*,scalar_t__,int) ; 
 int /*<<< orphan*/  debug ; 
 struct adv7393_std_info* stdinfo ; 
 struct adv7393_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,unsigned long long) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int adv7393_setstd(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct adv7393_state *state = to_state(sd);
	const struct adv7393_std_info *std_info;
	int num_std;
	u8 reg;
	u32 val;
	int err = 0;
	int i;

	num_std = ARRAY_SIZE(stdinfo);

	for (i = 0; i < num_std; i++) {
		if (stdinfo[i].stdid & std)
			break;
	}

	if (i == num_std) {
		v4l2_dbg(1, debug, sd,
				"Invalid std or std is not supported: %llx\n",
						(unsigned long long)std);
		return -EINVAL;
	}

	std_info = &stdinfo[i];

	/* Set the standard */
	val = state->reg80 & ~SD_STD_MASK;
	val |= std_info->standard_val3;
	err = adv7393_write(sd, ADV7393_SD_MODE_REG1, val);
	if (err < 0)
		goto setstd_exit;

	state->reg80 = val;

	/* Configure the input mode register */
	val = state->reg01 & ~INPUT_MODE_MASK;
	val |= SD_INPUT_MODE;
	err = adv7393_write(sd, ADV7393_MODE_SELECT_REG, val);
	if (err < 0)
		goto setstd_exit;

	state->reg01 = val;

	/* Program the sub carrier frequency registers */
	val = std_info->fsc_val;
	for (reg = ADV7393_FSC_REG0; reg <= ADV7393_FSC_REG3; reg++) {
		err = adv7393_write(sd, reg, val);
		if (err < 0)
			goto setstd_exit;
		val >>= 8;
	}

	val = state->reg82;

	/* Pedestal settings */
	if (std & (V4L2_STD_NTSC | V4L2_STD_NTSC_443))
		val |= SD_PEDESTAL_EN;
	else
		val &= SD_PEDESTAL_DI;

	err = adv7393_write(sd, ADV7393_SD_MODE_REG2, val);
	if (err < 0)
		goto setstd_exit;

	state->reg82 = val;

setstd_exit:
	if (err != 0)
		v4l2_err(sd, "Error setting std, write failed\n");

	return err;
}
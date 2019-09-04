#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct adv7343_state {int reg00; unsigned char reg02; unsigned char reg82; unsigned char reg35; TYPE_3__* pdata; } ;
struct TYPE_5__ {int* sd_dac_out; } ;
struct TYPE_4__ {int sleep_mode; int pll_control; int* dac; } ;
struct TYPE_6__ {TYPE_2__ sd_config; TYPE_1__ mode_config; } ;

/* Variables and functions */
 scalar_t__ ADV7343_COMPONENT_ID ; 
 unsigned char ADV7343_COMPONENT_POWER_VALUE ; 
 scalar_t__ ADV7343_COMPOSITE_ID ; 
 unsigned char ADV7343_COMPOSITE_POWER_VALUE ; 
 int /*<<< orphan*/  ADV7343_HD_MODE_REG6 ; 
 int /*<<< orphan*/  ADV7343_MODE_REG0 ; 
 int /*<<< orphan*/  ADV7343_POWER_MODE_REG ; 
 int /*<<< orphan*/  ADV7343_SD_MODE_REG2 ; 
 scalar_t__ ADV7343_SVIDEO_ID ; 
 unsigned char ADV7343_SVIDEO_POWER_VALUE ; 
 int EINVAL ; 
 unsigned char HD_DAC_SWAP_DI ; 
 unsigned char HD_RGB_INPUT_DI ; 
 unsigned char SD_DAC_1_DI ; 
 unsigned char SD_DAC_2_DI ; 
 unsigned char YUV_OUTPUT_SELECT ; 
 int adv7343_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  debug ; 
 struct adv7343_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,scalar_t__) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int adv7343_setoutput(struct v4l2_subdev *sd, u32 output_type)
{
	struct adv7343_state *state = to_state(sd);
	unsigned char val;
	int err = 0;

	if (output_type > ADV7343_SVIDEO_ID) {
		v4l2_dbg(1, debug, sd,
			"Invalid output type or output type not supported:%d\n",
								output_type);
		return -EINVAL;
	}

	/* Enable Appropriate DAC */
	val = state->reg00 & 0x03;

	/* configure default configuration */
	if (!state->pdata)
		if (output_type == ADV7343_COMPOSITE_ID)
			val |= ADV7343_COMPOSITE_POWER_VALUE;
		else if (output_type == ADV7343_COMPONENT_ID)
			val |= ADV7343_COMPONENT_POWER_VALUE;
		else
			val |= ADV7343_SVIDEO_POWER_VALUE;
	else
		val = state->pdata->mode_config.sleep_mode << 0 |
		      state->pdata->mode_config.pll_control << 1 |
		      state->pdata->mode_config.dac[2] << 2 |
		      state->pdata->mode_config.dac[1] << 3 |
		      state->pdata->mode_config.dac[0] << 4 |
		      state->pdata->mode_config.dac[5] << 5 |
		      state->pdata->mode_config.dac[4] << 6 |
		      state->pdata->mode_config.dac[3] << 7;

	err = adv7343_write(sd, ADV7343_POWER_MODE_REG, val);
	if (err < 0)
		goto setoutput_exit;

	state->reg00 = val;

	/* Enable YUV output */
	val = state->reg02 | YUV_OUTPUT_SELECT;
	err = adv7343_write(sd, ADV7343_MODE_REG0, val);
	if (err < 0)
		goto setoutput_exit;

	state->reg02 = val;

	/* configure SD DAC Output 2 and SD DAC Output 1 bit to zero */
	val = state->reg82 & (SD_DAC_1_DI & SD_DAC_2_DI);

	if (state->pdata && state->pdata->sd_config.sd_dac_out[0])
		val = val | (state->pdata->sd_config.sd_dac_out[0] << 1);
	else if (state->pdata && !state->pdata->sd_config.sd_dac_out[0])
		val = val & ~(state->pdata->sd_config.sd_dac_out[0] << 1);

	if (state->pdata && state->pdata->sd_config.sd_dac_out[1])
		val = val | (state->pdata->sd_config.sd_dac_out[1] << 2);
	else if (state->pdata && !state->pdata->sd_config.sd_dac_out[1])
		val = val & ~(state->pdata->sd_config.sd_dac_out[1] << 2);

	err = adv7343_write(sd, ADV7343_SD_MODE_REG2, val);
	if (err < 0)
		goto setoutput_exit;

	state->reg82 = val;

	/* configure ED/HD Color DAC Swap and ED/HD RGB Input Enable bit to
	 * zero */
	val = state->reg35 & (HD_RGB_INPUT_DI & HD_DAC_SWAP_DI);
	err = adv7343_write(sd, ADV7343_HD_MODE_REG6, val);
	if (err < 0)
		goto setoutput_exit;

	state->reg35 = val;

setoutput_exit:
	if (err != 0)
		v4l2_err(sd, "Error setting output, write failed\n");

	return err;
}
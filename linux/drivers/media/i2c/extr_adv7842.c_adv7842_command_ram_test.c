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
struct v4l2_subdev {int dummy; } ;
struct v4l2_dv_timings {int dummy; } ;
struct TYPE_2__ {struct adv7842_platform_data* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct adv7842_state {struct v4l2_dv_timings timings; int /*<<< orphan*/  vid_std_select; } ;
struct adv7842_platform_data {int /*<<< orphan*/  sd_ram_ddr; int /*<<< orphan*/  sd_ram_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7842_EDID_PORT_A ; 
 int /*<<< orphan*/  ADV7842_EDID_PORT_B ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  adv7842_core_init (struct v4l2_subdev*) ; 
 int adv7842_ddr_ram_test (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  adv7842_rewrite_i2c_addresses (struct v4l2_subdev*,struct adv7842_platform_data*) ; 
 int /*<<< orphan*/  adv7842_s_dv_timings (struct v4l2_subdev*,struct v4l2_dv_timings*) ; 
 int /*<<< orphan*/  disable_input (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  edid_write_hdmi_segment (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edid_write_vga_segment (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  enable_input (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  main_reset (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  memset (struct v4l2_dv_timings*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  select_input (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct adv7842_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int adv7842_command_ram_test(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct adv7842_state *state = to_state(sd);
	struct adv7842_platform_data *pdata = client->dev.platform_data;
	struct v4l2_dv_timings timings;
	int ret = 0;

	if (!pdata)
		return -ENODEV;

	if (!pdata->sd_ram_size || !pdata->sd_ram_ddr) {
		v4l2_info(sd, "no sdram or no ddr sdram\n");
		return -EINVAL;
	}

	main_reset(sd);

	adv7842_rewrite_i2c_addresses(sd, pdata);

	/* run ram test */
	ret = adv7842_ddr_ram_test(sd);

	main_reset(sd);

	adv7842_rewrite_i2c_addresses(sd, pdata);

	/* and re-init chip and state */
	adv7842_core_init(sd);

	disable_input(sd);

	select_input(sd, state->vid_std_select);

	enable_input(sd);

	edid_write_vga_segment(sd);
	edid_write_hdmi_segment(sd, ADV7842_EDID_PORT_A);
	edid_write_hdmi_segment(sd, ADV7842_EDID_PORT_B);

	timings = state->timings;

	memset(&state->timings, 0, sizeof(struct v4l2_dv_timings));

	adv7842_s_dv_timings(sd, &timings);

	return ret;
}
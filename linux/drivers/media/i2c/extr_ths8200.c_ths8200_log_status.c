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
typedef  int uint8_t ;
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct ths8200_state {int /*<<< orphan*/  dv_timings; int /*<<< orphan*/  chip_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  THS8200_CHIP_CTL ; 
 int /*<<< orphan*/  THS8200_DTG2_LINE_CNT_LSB ; 
 int /*<<< orphan*/  THS8200_DTG2_LINE_CNT_MSB ; 
 int /*<<< orphan*/  THS8200_DTG2_PIXEL_CNT_LSB ; 
 int /*<<< orphan*/  THS8200_DTG2_PIXEL_CNT_MSB ; 
 int ths8200_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct ths8200_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,...) ; 
 int /*<<< orphan*/  v4l2_print_dv_timings (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ths8200_log_status(struct v4l2_subdev *sd)
{
	struct ths8200_state *state = to_state(sd);
	uint8_t reg_03 = ths8200_read(sd, THS8200_CHIP_CTL);

	v4l2_info(sd, "----- Chip status -----\n");
	v4l2_info(sd, "version: %u\n", state->chip_version);
	v4l2_info(sd, "power: %s\n", (reg_03 & 0x0c) ? "off" : "on");
	v4l2_info(sd, "reset: %s\n", (reg_03 & 0x01) ? "off" : "on");
	v4l2_info(sd, "test pattern: %s\n",
		  (reg_03 & 0x20) ? "enabled" : "disabled");
	v4l2_info(sd, "format: %ux%u\n",
		  ths8200_read(sd, THS8200_DTG2_PIXEL_CNT_MSB) * 256 +
		  ths8200_read(sd, THS8200_DTG2_PIXEL_CNT_LSB),
		  (ths8200_read(sd, THS8200_DTG2_LINE_CNT_MSB) & 0x07) * 256 +
		  ths8200_read(sd, THS8200_DTG2_LINE_CNT_LSB));
	v4l2_print_dv_timings(sd->name, "Configured format:",
			      &state->dv_timings, true);
	return 0;
}
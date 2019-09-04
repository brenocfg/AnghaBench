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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct s5c73m3 {int isp_ready; struct v4l2_subdev sensor_sd; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const**) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int s5c73m3_read_fw_version (struct s5c73m3*) ; 
 int s5c73m3_system_status_wait (struct s5c73m3*,int,int,int) ; 
 int s5c73m3_write (struct s5c73m3*,int const,int const) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int s5c73m3_rom_boot(struct s5c73m3 *state, bool load_fw)
{
	static const u32 boot_regs[][2] = {
		{ 0x3100010c, 0x0044 },
		{ 0x31000108, 0x000d },
		{ 0x31000304, 0x0001 },
		{ 0x00010000, 0x5800 },
		{ 0x00010002, 0x0002 },
		{ 0x31000000, 0x0001 },
		{ 0x30100014, 0x1b85 },
		{ 0x30100010, 0x230c }
	};
	struct v4l2_subdev *sd = &state->sensor_sd;
	int i, ret;

	/* Run ARM MCU */
	ret = s5c73m3_write(state, 0x30000004, 0xffff);
	if (ret < 0)
		return ret;
	usleep_range(400, 450);

	/* Check booting status */
	ret = s5c73m3_system_status_wait(state, 0x0c, 100, 4);
	if (ret < 0) {
		v4l2_err(sd, "Booting failed: %d\n", ret);
		return ret;
	}

	for (i = 0; i < ARRAY_SIZE(boot_regs); i++) {
		ret = s5c73m3_write(state, boot_regs[i][0], boot_regs[i][1]);
		if (ret < 0)
			return ret;
	}
	msleep(200);

	/* Check the binary read status */
	ret = s5c73m3_system_status_wait(state, 0x230e, 1000, 150);
	if (ret < 0) {
		v4l2_err(sd, "Binary read failed: %d\n", ret);
		return ret;
	}

	/* ARM reset */
	ret = s5c73m3_write(state, 0x30000004, 0xfffd);
	if (ret < 0)
		return ret;
	/* Remap */
	ret = s5c73m3_write(state, 0x301000a4, 0x0183);
	if (ret < 0)
		return ret;
	/* MCU re-start */
	ret = s5c73m3_write(state, 0x30000004, 0xffff);
	if (ret < 0)
		return ret;

	state->isp_ready = 1;

	return s5c73m3_read_fw_version(state);
}
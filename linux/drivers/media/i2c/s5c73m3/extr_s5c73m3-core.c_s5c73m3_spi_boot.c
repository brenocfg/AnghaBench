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
struct s5c73m3 {struct v4l2_subdev sensor_sd; } ;

/* Variables and functions */
 int s5c73m3_fw_update_from (struct s5c73m3*) ; 
 int /*<<< orphan*/  s5c73m3_load_fw (struct v4l2_subdev*) ; 
 int s5c73m3_read_fw_version (struct s5c73m3*) ; 
 int s5c73m3_system_status_wait (struct s5c73m3*,int,int,int) ; 
 int s5c73m3_write (struct s5c73m3*,int,int) ; 
 scalar_t__ update_fw ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int s5c73m3_spi_boot(struct s5c73m3 *state, bool load_fw)
{
	struct v4l2_subdev *sd = &state->sensor_sd;
	int ret;

	/* Run ARM MCU */
	ret = s5c73m3_write(state, 0x30000004, 0xffff);
	if (ret < 0)
		return ret;

	usleep_range(400, 500);

	/* Check booting status */
	ret = s5c73m3_system_status_wait(state, 0x0c, 100, 3);
	if (ret < 0) {
		v4l2_err(sd, "booting failed: %d\n", ret);
		return ret;
	}

	/* P,M,S and Boot Mode */
	ret = s5c73m3_write(state, 0x30100014, 0x2146);
	if (ret < 0)
		return ret;

	ret = s5c73m3_write(state, 0x30100010, 0x210c);
	if (ret < 0)
		return ret;

	usleep_range(200, 250);

	/* Check SPI status */
	ret = s5c73m3_system_status_wait(state, 0x210d, 100, 300);
	if (ret < 0)
		v4l2_err(sd, "SPI not ready: %d\n", ret);

	/* Firmware download over SPI */
	if (load_fw)
		s5c73m3_load_fw(sd);

	/* MCU reset */
	ret = s5c73m3_write(state, 0x30000004, 0xfffd);
	if (ret < 0)
		return ret;

	/* Remap */
	ret = s5c73m3_write(state, 0x301000a4, 0x0183);
	if (ret < 0)
		return ret;

	/* MCU restart */
	ret = s5c73m3_write(state, 0x30000004, 0xffff);
	if (ret < 0 || !load_fw)
		return ret;

	ret = s5c73m3_read_fw_version(state);
	if (ret < 0)
		return ret;

	if (load_fw && update_fw) {
		ret = s5c73m3_fw_update_from(state);
		update_fw = 0;
	}

	return ret;
}
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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct s5c73m3 {char* sensor_fw; char* sensor_type; int fw_size; scalar_t__ isp_ready; struct v4l2_subdev sensor_sd; } ;

/* Variables and functions */
 int S5C73M3_SENSOR_FW_LEN ; 
 int S5C73M3_SENSOR_TYPE_LEN ; 
 int s5c73m3_read (struct s5c73m3*,int,int*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,char*,char*) ; 

__attribute__((used)) static int s5c73m3_read_fw_version(struct s5c73m3 *state)
{
	struct v4l2_subdev *sd = &state->sensor_sd;
	int i, ret;
	u16 data[2];
	int offset;

	offset = state->isp_ready ? 0x60 : 0;

	for (i = 0; i < S5C73M3_SENSOR_FW_LEN / 2; i++) {
		ret = s5c73m3_read(state, offset + i * 2, data);
		if (ret < 0)
			return ret;
		state->sensor_fw[i * 2] = (char)(*data & 0xff);
		state->sensor_fw[i * 2 + 1] = (char)(*data >> 8);
	}
	state->sensor_fw[S5C73M3_SENSOR_FW_LEN] = '\0';


	for (i = 0; i < S5C73M3_SENSOR_TYPE_LEN / 2; i++) {
		ret = s5c73m3_read(state, offset + 6 + i * 2, data);
		if (ret < 0)
			return ret;
		state->sensor_type[i * 2] = (char)(*data & 0xff);
		state->sensor_type[i * 2 + 1] = (char)(*data >> 8);
	}
	state->sensor_type[S5C73M3_SENSOR_TYPE_LEN] = '\0';

	ret = s5c73m3_read(state, offset + 0x14, data);
	if (ret >= 0) {
		ret = s5c73m3_read(state, offset + 0x16, data + 1);
		if (ret >= 0)
			state->fw_size = data[0] + (data[1] << 16);
	}

	v4l2_info(sd, "Sensor type: %s, FW version: %s\n",
		  state->sensor_type, state->sensor_fw);
	return ret;
}
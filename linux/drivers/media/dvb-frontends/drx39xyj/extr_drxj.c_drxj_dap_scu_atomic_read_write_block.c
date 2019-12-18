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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct i2c_device_addr {int dummy; } ;
struct drxjscu_cmd {int parameter_len; int result_len; int command; int* result; int* parameter; } ;

/* Variables and functions */
 scalar_t__ ADDR_AT_SCU_SPACE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int SCU_RAM_COMMAND_CMD_AUX_SCU_ATOMIC_ACCESS ; 
 int SCU_RAM_COMMAND_STANDARD_TOP ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int scu_command (struct i2c_device_addr*,struct drxjscu_cmd*) ; 

__attribute__((used)) static
int drxj_dap_scu_atomic_read_write_block(struct i2c_device_addr *dev_addr, u32 addr, u16 datasize,	/* max 30 bytes because the limit of SCU parameter */
					      u8 *data, bool read_flag)
{
	struct drxjscu_cmd scu_cmd;
	int rc;
	u16 set_param_parameters[18];
	u16 cmd_result[15];

	/* Parameter check */
	if (!data || !dev_addr || (datasize % 2) || ((datasize / 2) > 16))
		return -EINVAL;

	set_param_parameters[1] = (u16) ADDR_AT_SCU_SPACE(addr);
	if (read_flag) {		/* read */
		set_param_parameters[0] = ((~(0x0080)) & datasize);
		scu_cmd.parameter_len = 2;
		scu_cmd.result_len = datasize / 2 + 2;
	} else {
		int i = 0;

		set_param_parameters[0] = 0x0080 | datasize;
		for (i = 0; i < (datasize / 2); i++) {
			set_param_parameters[i + 2] =
			    (data[2 * i] | (data[(2 * i) + 1] << 8));
		}
		scu_cmd.parameter_len = datasize / 2 + 2;
		scu_cmd.result_len = 1;
	}

	scu_cmd.command =
	    SCU_RAM_COMMAND_STANDARD_TOP |
	    SCU_RAM_COMMAND_CMD_AUX_SCU_ATOMIC_ACCESS;
	scu_cmd.result = cmd_result;
	scu_cmd.parameter = set_param_parameters;
	rc = scu_command(dev_addr, &scu_cmd);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	if (read_flag) {
		int i = 0;
		/* read data from buffer */
		for (i = 0; i < (datasize / 2); i++) {
			data[2 * i] = (u8) (scu_cmd.result[i + 2] & 0xFF);
			data[(2 * i) + 1] = (u8) (scu_cmd.result[i + 2] >> 8);
		}
	}

	return 0;

rw_error:
	return rc;

}
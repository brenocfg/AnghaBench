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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_device_addr {int dummy; } ;
struct drxjscu_cmd {int command; int result_len; int /*<<< orphan*/ * result; int /*<<< orphan*/ * parameter; scalar_t__ parameter_len; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct drx_demod_instance {struct drx_common_attr* my_common_attr; struct i2c_device_addr* my_i2c_dev_addr; } ;
struct drx_common_attr {int /*<<< orphan*/  mpeg_cfg; } ;
struct drx_cfg_mpeg_output {int enable_mpeg_output; } ;
typedef  int /*<<< orphan*/  cfg_mpeg_output ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_COMM_EXEC_STOP ; 
 int /*<<< orphan*/  FEC_COMM_EXEC__A ; 
 int /*<<< orphan*/  IQM_CF_COMM_EXEC_STOP ; 
 int /*<<< orphan*/  IQM_CF_COMM_EXEC__A ; 
 int /*<<< orphan*/  IQM_COMM_EXEC_STOP ; 
 int /*<<< orphan*/  IQM_COMM_EXEC__A ; 
 int /*<<< orphan*/  IQM_FD_COMM_EXEC_STOP ; 
 int /*<<< orphan*/  IQM_FD_COMM_EXEC__A ; 
 int /*<<< orphan*/  IQM_FS_COMM_EXEC_STOP ; 
 int /*<<< orphan*/  IQM_FS_COMM_EXEC__A ; 
 int /*<<< orphan*/  IQM_RC_COMM_EXEC_STOP ; 
 int /*<<< orphan*/  IQM_RC_COMM_EXEC__A ; 
 int /*<<< orphan*/  IQM_RT_COMM_EXEC_STOP ; 
 int /*<<< orphan*/  IQM_RT_COMM_EXEC__A ; 
 int /*<<< orphan*/  QAM_COMM_EXEC_STOP ; 
 int /*<<< orphan*/  QAM_COMM_EXEC__A ; 
 int SCU_RAM_COMMAND_CMD_DEMOD_STOP ; 
 int SCU_RAM_COMMAND_STANDARD_QAM ; 
 int ctrl_set_cfg_mpeg_output (struct drx_demod_instance*,struct drx_cfg_mpeg_output*) ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct drx_cfg_mpeg_output*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int scu_command (struct i2c_device_addr*,struct drxjscu_cmd*) ; 
 int set_iqm_af (struct drx_demod_instance*,int) ; 

__attribute__((used)) static int power_down_qam(struct drx_demod_instance *demod, bool primary)
{
	struct drxjscu_cmd cmd_scu = { /* command      */ 0,
		/* parameter_len */ 0,
		/* result_len    */ 0,
		/* *parameter   */ NULL,
		/* *result      */ NULL
	};
	int rc;
	struct i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	struct drx_cfg_mpeg_output cfg_mpeg_output;
	struct drx_common_attr *common_attr = demod->my_common_attr;
	u16 cmd_result = 0;

	/*
	   STOP demodulator
	   resets IQM, QAM and FEC HW blocks
	 */
	/* stop all comm_exec */
	rc = drxj_dap_write_reg16(dev_addr, FEC_COMM_EXEC__A, FEC_COMM_EXEC_STOP, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, QAM_COMM_EXEC__A, QAM_COMM_EXEC_STOP, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	cmd_scu.command = SCU_RAM_COMMAND_STANDARD_QAM |
	    SCU_RAM_COMMAND_CMD_DEMOD_STOP;
	cmd_scu.parameter_len = 0;
	cmd_scu.result_len = 1;
	cmd_scu.parameter = NULL;
	cmd_scu.result = &cmd_result;
	rc = scu_command(dev_addr, &cmd_scu);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	if (primary) {
		rc = drxj_dap_write_reg16(dev_addr, IQM_COMM_EXEC__A, IQM_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = set_iqm_af(demod, false);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	} else {
		rc = drxj_dap_write_reg16(dev_addr, IQM_FS_COMM_EXEC__A, IQM_FS_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, IQM_FD_COMM_EXEC__A, IQM_FD_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, IQM_RC_COMM_EXEC__A, IQM_RC_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, IQM_RT_COMM_EXEC__A, IQM_RT_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, IQM_CF_COMM_EXEC__A, IQM_CF_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	}

	memcpy(&cfg_mpeg_output, &common_attr->mpeg_cfg, sizeof(cfg_mpeg_output));
	cfg_mpeg_output.enable_mpeg_output = false;

	rc = ctrl_set_cfg_mpeg_output(demod, &cfg_mpeg_output);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	return 0;
rw_error:
	return rc;
}
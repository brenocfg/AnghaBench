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
typedef  scalar_t__ u16 ;
struct i2c_device_addr {int dummy; } ;
struct drxjscu_cmd {int parameter_len; int result_len; scalar_t__* result; int /*<<< orphan*/  command; int /*<<< orphan*/ * parameter; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  DRXJ_MAX_WAITTIME ; 
 scalar_t__ DRX_SCU_READY ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  SCU_RAM_COMMAND__A ; 
 scalar_t__ SCU_RAM_PARAM_0_RESULT_INVPAR ; 
 scalar_t__ SCU_RAM_PARAM_0_RESULT_SIZE ; 
 scalar_t__ SCU_RAM_PARAM_0_RESULT_UNKCMD ; 
 scalar_t__ SCU_RAM_PARAM_0_RESULT_UNKSTD ; 
 int /*<<< orphan*/  SCU_RAM_PARAM_0__A ; 
 int /*<<< orphan*/  SCU_RAM_PARAM_1__A ; 
 int /*<<< orphan*/  SCU_RAM_PARAM_2__A ; 
 int /*<<< orphan*/  SCU_RAM_PARAM_3__A ; 
 int /*<<< orphan*/  SCU_RAM_PARAM_4__A ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int scu_command(struct i2c_device_addr *dev_addr, struct drxjscu_cmd *cmd)
{
	int rc;
	u16 cur_cmd = 0;
	unsigned long timeout;

	/* Check param */
	if (cmd == NULL)
		return -EINVAL;

	/* Wait until SCU command interface is ready to receive command */
	rc = drxj_dap_read_reg16(dev_addr, SCU_RAM_COMMAND__A, &cur_cmd, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	if (cur_cmd != DRX_SCU_READY)
		return -EIO;

	switch (cmd->parameter_len) {
	case 5:
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_PARAM_4__A, *(cmd->parameter + 4), 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}	/* fallthrough */
	case 4:
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_PARAM_3__A, *(cmd->parameter + 3), 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}	/* fallthrough */
	case 3:
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_PARAM_2__A, *(cmd->parameter + 2), 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}	/* fallthrough */
	case 2:
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_PARAM_1__A, *(cmd->parameter + 1), 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}	/* fallthrough */
	case 1:
		rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_PARAM_0__A, *(cmd->parameter + 0), 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}	/* fallthrough */
	case 0:
		/* do nothing */
		break;
	default:
		/* this number of parameters is not supported */
		return -EIO;
	}
	rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_COMMAND__A, cmd->command, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	/* Wait until SCU has processed command */
	timeout = jiffies + msecs_to_jiffies(DRXJ_MAX_WAITTIME);
	while (time_is_after_jiffies(timeout)) {
		rc = drxj_dap_read_reg16(dev_addr, SCU_RAM_COMMAND__A, &cur_cmd, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		if (cur_cmd == DRX_SCU_READY)
			break;
		usleep_range(1000, 2000);
	}

	if (cur_cmd != DRX_SCU_READY)
		return -EIO;

	/* read results */
	if ((cmd->result_len > 0) && (cmd->result != NULL)) {
		s16 err;

		switch (cmd->result_len) {
		case 4:
			rc = drxj_dap_read_reg16(dev_addr, SCU_RAM_PARAM_3__A, cmd->result + 3, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}	/* fallthrough */
		case 3:
			rc = drxj_dap_read_reg16(dev_addr, SCU_RAM_PARAM_2__A, cmd->result + 2, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}	/* fallthrough */
		case 2:
			rc = drxj_dap_read_reg16(dev_addr, SCU_RAM_PARAM_1__A, cmd->result + 1, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}	/* fallthrough */
		case 1:
			rc = drxj_dap_read_reg16(dev_addr, SCU_RAM_PARAM_0__A, cmd->result + 0, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}	/* fallthrough */
		case 0:
			/* do nothing */
			break;
		default:
			/* this number of parameters is not supported */
			return -EIO;
		}

		/* Check if an error was reported by SCU */
		err = cmd->result[0];

		/* check a few fixed error codes */
		if ((err == (s16) SCU_RAM_PARAM_0_RESULT_UNKSTD)
		    || (err == (s16) SCU_RAM_PARAM_0_RESULT_UNKCMD)
		    || (err == (s16) SCU_RAM_PARAM_0_RESULT_INVPAR)
		    || (err == (s16) SCU_RAM_PARAM_0_RESULT_SIZE)
		    ) {
			return -EINVAL;
		}
		/* here it is assumed that negative means error, and positive no error */
		else if (err < 0)
			return -EIO;
		else
			return 0;
	}

	return 0;

rw_error:
	return rc;
}
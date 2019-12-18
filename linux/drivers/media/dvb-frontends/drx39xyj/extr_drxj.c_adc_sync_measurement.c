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
struct i2c_device_addr {int dummy; } ;
struct drx_demod_instance {struct i2c_device_addr* my_i2c_dev_addr; } ;

/* Variables and functions */
 int IQM_AF_COMM_EXEC_ACTIVE ; 
 int /*<<< orphan*/  IQM_AF_COMM_EXEC__A ; 
 int /*<<< orphan*/  IQM_AF_PHASE0__A ; 
 int /*<<< orphan*/  IQM_AF_PHASE1__A ; 
 int /*<<< orphan*/  IQM_AF_PHASE2__A ; 
 int /*<<< orphan*/  IQM_AF_START_LOCK__A ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int adc_sync_measurement(struct drx_demod_instance *demod, u16 *count)
{
	struct i2c_device_addr *dev_addr = NULL;
	int rc;
	u16 data = 0;

	dev_addr = demod->my_i2c_dev_addr;

	/* Start measurement */
	rc = drxj_dap_write_reg16(dev_addr, IQM_AF_COMM_EXEC__A, IQM_AF_COMM_EXEC_ACTIVE, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, IQM_AF_START_LOCK__A, 1, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	/* Wait at least 3*128*(1/sysclk) <<< 1 millisec */
	msleep(1);

	*count = 0;
	rc = drxj_dap_read_reg16(dev_addr, IQM_AF_PHASE0__A, &data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	if (data == 127)
		*count = *count + 1;
	rc = drxj_dap_read_reg16(dev_addr, IQM_AF_PHASE1__A, &data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	if (data == 127)
		*count = *count + 1;
	rc = drxj_dap_read_reg16(dev_addr, IQM_AF_PHASE2__A, &data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	if (data == 127)
		*count = *count + 1;

	return 0;
rw_error:
	return rc;
}
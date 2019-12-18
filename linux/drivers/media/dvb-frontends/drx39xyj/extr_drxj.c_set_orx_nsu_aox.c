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
 int ORX_NSU_AOX_STDBY_W_STDBYADC_A2_ON ; 
 int ORX_NSU_AOX_STDBY_W_STDBYAMP_A2_ON ; 
 int ORX_NSU_AOX_STDBY_W_STDBYBIAS_A2_ON ; 
 int ORX_NSU_AOX_STDBY_W_STDBYFLT_A2_ON ; 
 int ORX_NSU_AOX_STDBY_W_STDBYPD_A2_ON ; 
 int ORX_NSU_AOX_STDBY_W_STDBYPLL_A2_ON ; 
 int ORX_NSU_AOX_STDBY_W_STDBYTAGC_IF_A2_ON ; 
 int ORX_NSU_AOX_STDBY_W_STDBYTAGC_RF_A2_ON ; 
 int /*<<< orphan*/  ORX_NSU_AOX_STDBY_W__A ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int set_orx_nsu_aox(struct drx_demod_instance *demod, bool active)
{
	struct i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	int rc;
	u16 data = 0;

	/* Configure NSU_AOX */
	rc = drxj_dap_read_reg16(dev_addr, ORX_NSU_AOX_STDBY_W__A, &data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	if (!active)
		data &= ((~ORX_NSU_AOX_STDBY_W_STDBYADC_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYAMP_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYBIAS_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYPLL_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYPD_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYTAGC_IF_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYTAGC_RF_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYFLT_A2_ON));
	else
		data |= (ORX_NSU_AOX_STDBY_W_STDBYADC_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYAMP_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYBIAS_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYPLL_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYPD_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYTAGC_IF_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYTAGC_RF_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYFLT_A2_ON);
	rc = drxj_dap_write_reg16(dev_addr, ORX_NSU_AOX_STDBY_W__A, data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	return 0;
rw_error:
	return rc;
}
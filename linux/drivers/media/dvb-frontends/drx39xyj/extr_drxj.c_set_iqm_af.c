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
 int IQM_AF_STDBY_STDBY_ADC_A2_ACTIVE ; 
 int IQM_AF_STDBY_STDBY_AMP_A2_ACTIVE ; 
 int IQM_AF_STDBY_STDBY_PD_A2_ACTIVE ; 
 int IQM_AF_STDBY_STDBY_TAGC_IF_A2_ACTIVE ; 
 int IQM_AF_STDBY_STDBY_TAGC_RF_A2_ACTIVE ; 
 int /*<<< orphan*/  IQM_AF_STDBY__A ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int set_iqm_af(struct drx_demod_instance *demod, bool active)
{
	u16 data = 0;
	struct i2c_device_addr *dev_addr = NULL;
	int rc;

	dev_addr = demod->my_i2c_dev_addr;

	/* Configure IQM */
	rc = drxj_dap_read_reg16(dev_addr, IQM_AF_STDBY__A, &data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	if (!active)
		data &= ((~IQM_AF_STDBY_STDBY_ADC_A2_ACTIVE) & (~IQM_AF_STDBY_STDBY_AMP_A2_ACTIVE) & (~IQM_AF_STDBY_STDBY_PD_A2_ACTIVE) & (~IQM_AF_STDBY_STDBY_TAGC_IF_A2_ACTIVE) & (~IQM_AF_STDBY_STDBY_TAGC_RF_A2_ACTIVE));
	else
		data |= (IQM_AF_STDBY_STDBY_ADC_A2_ACTIVE | IQM_AF_STDBY_STDBY_AMP_A2_ACTIVE | IQM_AF_STDBY_STDBY_PD_A2_ACTIVE | IQM_AF_STDBY_STDBY_TAGC_IF_A2_ACTIVE | IQM_AF_STDBY_STDBY_TAGC_RF_A2_ACTIVE);
	rc = drxj_dap_write_reg16(dev_addr, IQM_AF_STDBY__A, data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	return 0;
rw_error:
	return rc;
}
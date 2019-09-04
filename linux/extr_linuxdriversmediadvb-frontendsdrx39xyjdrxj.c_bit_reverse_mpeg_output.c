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
struct drxj_data {scalar_t__ bit_reverse_mpeg_outout; } ;
struct drx_demod_instance {scalar_t__ my_ext_attr; struct i2c_device_addr* my_i2c_dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_OC_IPR_MODE_REVERSE_ORDER__M ; 
 int /*<<< orphan*/  FEC_OC_IPR_MODE__A ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int bit_reverse_mpeg_output(struct drx_demod_instance *demod)
{
	struct drxj_data *ext_attr = (struct drxj_data *) (NULL);
	struct i2c_device_addr *dev_addr = (struct i2c_device_addr *)(NULL);
	int rc;
	u16 fec_oc_ipr_mode = 0;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (struct drxj_data *) demod->my_ext_attr;

	rc = drxj_dap_read_reg16(dev_addr, FEC_OC_IPR_MODE__A, &fec_oc_ipr_mode, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	/* reset to default (normal bit order) */
	fec_oc_ipr_mode &= (~FEC_OC_IPR_MODE_REVERSE_ORDER__M);

	if (ext_attr->bit_reverse_mpeg_outout)
		fec_oc_ipr_mode |= FEC_OC_IPR_MODE_REVERSE_ORDER__M;

	rc = drxj_dap_write_reg16(dev_addr, FEC_OC_IPR_MODE__A, fec_oc_ipr_mode, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	return 0;
rw_error:
	return rc;
}
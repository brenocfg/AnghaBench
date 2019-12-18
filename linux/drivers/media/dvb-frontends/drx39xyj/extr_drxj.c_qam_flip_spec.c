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
typedef  int u16 ;
struct i2c_device_addr {int dummy; } ;
struct drxj_data {int iqm_fs_rate_ofs; int pos_image; } ;
struct drx_demod_instance {struct drxj_data* my_ext_attr; struct i2c_device_addr* my_i2c_dev_addr; } ;
struct drx_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IQM_FS_RATE_LO__A ; 
 int /*<<< orphan*/  IQM_FS_RATE_OFS_LO__A ; 
 scalar_t__ QAM_DQ_MODE__A ; 
 scalar_t__ QAM_DQ_TAP_IM_EL0__A ; 
 scalar_t__ QAM_FQ_LA_FACTOR__A ; 
 scalar_t__ QAM_FQ_MODE__A ; 
 scalar_t__ QAM_FQ_TAP_IM_EL0__A ; 
 scalar_t__ QAM_LC_CF1__A ; 
 scalar_t__ QAM_LC_CF__A ; 
 scalar_t__ QAM_LC_CI__A ; 
 scalar_t__ QAM_LC_EP__A ; 
 int SCU_RAM_QAM_CTL_ENA_ACQ__M ; 
 int SCU_RAM_QAM_CTL_ENA_EQU__M ; 
 int SCU_RAM_QAM_CTL_ENA_LC__M ; 
 scalar_t__ SCU_RAM_QAM_CTL_ENA__A ; 
 scalar_t__ SCU_RAM_QAM_FSM_STATE_TGT__A ; 
 scalar_t__ SCU_RAM_QAM_FSM_STATE__A ; 
 int drxdap_fasi_write_reg32 (struct i2c_device_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drxj_dap_atomic_read_reg32 (struct i2c_device_addr*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int qam_flip_spec(struct drx_demod_instance *demod, struct drx_channel *channel)
{
	struct i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	struct drxj_data *ext_attr = demod->my_ext_attr;
	int rc;
	u32 iqm_fs_rate_ofs = 0;
	u32 iqm_fs_rate_lo = 0;
	u16 qam_ctl_ena = 0;
	u16 data = 0;
	u16 equ_mode = 0;
	u16 fsm_state = 0;
	int i = 0;
	int ofsofs = 0;

	/* Silence the controlling of lc, equ, and the acquisition state machine */
	rc = drxj_dap_read_reg16(dev_addr, SCU_RAM_QAM_CTL_ENA__A, &qam_ctl_ena, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_QAM_CTL_ENA__A, qam_ctl_ena & ~(SCU_RAM_QAM_CTL_ENA_ACQ__M | SCU_RAM_QAM_CTL_ENA_EQU__M | SCU_RAM_QAM_CTL_ENA_LC__M), 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	/* freeze the frequency control loop */
	rc = drxj_dap_write_reg16(dev_addr, QAM_LC_CF__A, 0, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, QAM_LC_CF1__A, 0, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	rc = drxj_dap_atomic_read_reg32(dev_addr, IQM_FS_RATE_OFS_LO__A, &iqm_fs_rate_ofs, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_atomic_read_reg32(dev_addr, IQM_FS_RATE_LO__A, &iqm_fs_rate_lo, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	ofsofs = iqm_fs_rate_lo - iqm_fs_rate_ofs;
	iqm_fs_rate_ofs = ~iqm_fs_rate_ofs + 1;
	iqm_fs_rate_ofs -= 2 * ofsofs;

	/* freeze dq/fq updating */
	rc = drxj_dap_read_reg16(dev_addr, QAM_DQ_MODE__A, &data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	data = (data & 0xfff9);
	rc = drxj_dap_write_reg16(dev_addr, QAM_DQ_MODE__A, data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, QAM_FQ_MODE__A, data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	/* lc_cp / _ci / _ca */
	rc = drxj_dap_write_reg16(dev_addr, QAM_LC_CI__A, 0, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, QAM_LC_EP__A, 0, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, QAM_FQ_LA_FACTOR__A, 0, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	/* flip the spec */
	rc = drxdap_fasi_write_reg32(dev_addr, IQM_FS_RATE_OFS_LO__A, iqm_fs_rate_ofs, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	ext_attr->iqm_fs_rate_ofs = iqm_fs_rate_ofs;
	ext_attr->pos_image = (ext_attr->pos_image) ? false : true;

	/* freeze dq/fq updating */
	rc = drxj_dap_read_reg16(dev_addr, QAM_DQ_MODE__A, &data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	equ_mode = data;
	data = (data & 0xfff9);
	rc = drxj_dap_write_reg16(dev_addr, QAM_DQ_MODE__A, data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, QAM_FQ_MODE__A, data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	for (i = 0; i < 28; i++) {
		rc = drxj_dap_read_reg16(dev_addr, QAM_DQ_TAP_IM_EL0__A + (2 * i), &data, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, QAM_DQ_TAP_IM_EL0__A + (2 * i), -data, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	}

	for (i = 0; i < 24; i++) {
		rc = drxj_dap_read_reg16(dev_addr, QAM_FQ_TAP_IM_EL0__A + (2 * i), &data, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, QAM_FQ_TAP_IM_EL0__A + (2 * i), -data, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	}

	data = equ_mode;
	rc = drxj_dap_write_reg16(dev_addr, QAM_DQ_MODE__A, data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, QAM_FQ_MODE__A, data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_QAM_FSM_STATE_TGT__A, 4, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	i = 0;
	while ((fsm_state != 4) && (i++ < 100)) {
		rc = drxj_dap_read_reg16(dev_addr, SCU_RAM_QAM_FSM_STATE__A, &fsm_state, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	}
	rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_QAM_CTL_ENA__A, (qam_ctl_ena | 0x0016), 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	return 0;
rw_error:
	return rc;

}
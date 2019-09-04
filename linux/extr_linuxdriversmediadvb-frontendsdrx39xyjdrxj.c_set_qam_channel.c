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
struct drxj_data {int constellation; void* mirror; int /*<<< orphan*/  standard; } ;
struct drx_demod_instance {int /*<<< orphan*/  my_i2c_dev_addr; scalar_t__ my_ext_attr; } ;
struct drx_channel {int constellation; void* mirror; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum drx_lock_status { ____Placeholder_drx_lock_status } drx_lock_status ;

/* Variables and functions */
#define  DRX_CONSTELLATION_AUTO 133 
#define  DRX_CONSTELLATION_QAM128 132 
#define  DRX_CONSTELLATION_QAM16 131 
#define  DRX_CONSTELLATION_QAM256 130 
#define  DRX_CONSTELLATION_QAM32 129 
#define  DRX_CONSTELLATION_QAM64 128 
 int DRX_LOCKED ; 
 void* DRX_MIRROR_AUTO ; 
 void* DRX_MIRROR_NO ; 
 int DRX_NOT_LOCKED ; 
 int /*<<< orphan*/  DRX_STANDARD_ITU_B ; 
 int /*<<< orphan*/  DRX_STANDARD_ITU_C ; 
 int EINVAL ; 
 int /*<<< orphan*/  QAM_SET_OP_ALL ; 
 int /*<<< orphan*/  QAM_SET_OP_CONSTELLATION ; 
 int SCU_RAM_QAM_CTL_ENA_ACQ__M ; 
 int /*<<< orphan*/  SCU_RAM_QAM_CTL_ENA__A ; 
 int /*<<< orphan*/  SCU_RAM_QAM_FSM_STATE_TGT__A ; 
 int drxj_dap_read_reg16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_reg16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int qam256auto (struct drx_demod_instance*,struct drx_channel*,int /*<<< orphan*/ ,int*) ; 
 int qam64auto (struct drx_demod_instance*,struct drx_channel*,int /*<<< orphan*/ ,int*) ; 
 int set_qam (struct drx_demod_instance*,struct drx_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_qam_channel(struct drx_demod_instance *demod,
	       struct drx_channel *channel, s32 tuner_freq_offset)
{
	struct drxj_data *ext_attr = NULL;
	int rc;
	enum drx_lock_status lock_status = DRX_NOT_LOCKED;
	bool auto_flag = false;

	/* external attributes for storing acquired channel constellation */
	ext_attr = (struct drxj_data *) demod->my_ext_attr;

	/* set QAM channel constellation */
	switch (channel->constellation) {
	case DRX_CONSTELLATION_QAM16:
	case DRX_CONSTELLATION_QAM32:
	case DRX_CONSTELLATION_QAM128:
		return -EINVAL;
	case DRX_CONSTELLATION_QAM64:
	case DRX_CONSTELLATION_QAM256:
		if (ext_attr->standard != DRX_STANDARD_ITU_B)
			return -EINVAL;

		ext_attr->constellation = channel->constellation;
		if (channel->mirror == DRX_MIRROR_AUTO)
			ext_attr->mirror = DRX_MIRROR_NO;
		else
			ext_attr->mirror = channel->mirror;

		rc = set_qam(demod, channel, tuner_freq_offset, QAM_SET_OP_ALL);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}

		if (channel->constellation == DRX_CONSTELLATION_QAM64)
			rc = qam64auto(demod, channel, tuner_freq_offset,
				       &lock_status);
		else
			rc = qam256auto(demod, channel, tuner_freq_offset,
					&lock_status);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
	case DRX_CONSTELLATION_AUTO:	/* for channel scan */
		if (ext_attr->standard == DRX_STANDARD_ITU_B) {
			u16 qam_ctl_ena = 0;

			auto_flag = true;

			/* try to lock default QAM constellation: QAM256 */
			channel->constellation = DRX_CONSTELLATION_QAM256;
			ext_attr->constellation = DRX_CONSTELLATION_QAM256;
			if (channel->mirror == DRX_MIRROR_AUTO)
				ext_attr->mirror = DRX_MIRROR_NO;
			else
				ext_attr->mirror = channel->mirror;
			rc = set_qam(demod, channel, tuner_freq_offset,
				     QAM_SET_OP_ALL);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = qam256auto(demod, channel, tuner_freq_offset,
					&lock_status);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}

			if (lock_status >= DRX_LOCKED) {
				channel->constellation = DRX_CONSTELLATION_AUTO;
				break;
			}

			/* QAM254 not locked. Try QAM64 constellation */
			channel->constellation = DRX_CONSTELLATION_QAM64;
			ext_attr->constellation = DRX_CONSTELLATION_QAM64;
			if (channel->mirror == DRX_MIRROR_AUTO)
				ext_attr->mirror = DRX_MIRROR_NO;
			else
				ext_attr->mirror = channel->mirror;

			rc = drxj_dap_read_reg16(demod->my_i2c_dev_addr,
						     SCU_RAM_QAM_CTL_ENA__A,
						     &qam_ctl_ena, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_CTL_ENA__A,
						      qam_ctl_ena & ~SCU_RAM_QAM_CTL_ENA_ACQ__M, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_FSM_STATE_TGT__A,
						      0x2, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}	/* force to rate hunting */

			rc = set_qam(demod, channel, tuner_freq_offset,
				     QAM_SET_OP_CONSTELLATION);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_CTL_ENA__A,
						      qam_ctl_ena, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}

			rc = qam64auto(demod, channel, tuner_freq_offset,
				       &lock_status);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}

			channel->constellation = DRX_CONSTELLATION_AUTO;
		} else if (ext_attr->standard == DRX_STANDARD_ITU_C) {
			u16 qam_ctl_ena = 0;

			channel->constellation = DRX_CONSTELLATION_QAM64;
			ext_attr->constellation = DRX_CONSTELLATION_QAM64;
			auto_flag = true;

			if (channel->mirror == DRX_MIRROR_AUTO)
				ext_attr->mirror = DRX_MIRROR_NO;
			else
				ext_attr->mirror = channel->mirror;
			rc = drxj_dap_read_reg16(demod->my_i2c_dev_addr,
						     SCU_RAM_QAM_CTL_ENA__A,
						     &qam_ctl_ena, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_CTL_ENA__A,
						      qam_ctl_ena & ~SCU_RAM_QAM_CTL_ENA_ACQ__M, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_FSM_STATE_TGT__A,
						      0x2, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}	/* force to rate hunting */

			rc = set_qam(demod, channel, tuner_freq_offset,
				     QAM_SET_OP_CONSTELLATION);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = drxj_dap_write_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_CTL_ENA__A,
						      qam_ctl_ena, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			rc = qam64auto(demod, channel, tuner_freq_offset,
				       &lock_status);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			channel->constellation = DRX_CONSTELLATION_AUTO;
		} else {
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
rw_error:
	/* restore starting value */
	if (auto_flag)
		channel->constellation = DRX_CONSTELLATION_AUTO;
	return rc;
}
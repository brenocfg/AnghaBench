#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct cxd2880_tnrdmd_pid_ftr_cfg {int dummy; } ;
struct TYPE_4__ {int xtal_share_type; scalar_t__ ts_output_if; } ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; int clk_mode; struct cxd2880_tnrdmd_pid_ftr_cfg pid_ftr_cfg; scalar_t__ pid_ftr_cfg_en; TYPE_1__ create_param; struct cxd2880_tnrdmd* diver_sub; int /*<<< orphan*/  is_cable_input; TYPE_2__* io; } ;
typedef  enum cxd2880_tnrdmd_clockmode { ____Placeholder_cxd2880_tnrdmd_clockmode } cxd2880_tnrdmd_clockmode ;
typedef  enum cxd2880_dtv_sys { ____Placeholder_cxd2880_dtv_sys } cxd2880_dtv_sys ;
typedef  enum cxd2880_dtv_bandwidth { ____Placeholder_cxd2880_dtv_bandwidth } cxd2880_dtv_bandwidth ;
struct TYPE_5__ {int (* write_reg ) (TYPE_2__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
#define  CXD2880_DTV_SYS_DVBT 133 
#define  CXD2880_DTV_SYS_DVBT2 132 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
 int CXD2880_TNRDMD_CLOCKMODE_A ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
 scalar_t__ CXD2880_TNRDMD_TSOUT_IF_TS ; 
#define  CXD2880_TNRDMD_XTAL_SHARE_EXTREF 131 
#define  CXD2880_TNRDMD_XTAL_SHARE_MASTER 130 
#define  CXD2880_TNRDMD_XTAL_SHARE_NONE 129 
#define  CXD2880_TNRDMD_XTAL_SHARE_SLAVE 128 
 int EINVAL ; 
 int cxd2880_tnrdmd_check_internal_cpu_status (struct cxd2880_tnrdmd*,int*) ; 
 int cxd2880_tnrdmd_sleep (struct cxd2880_tnrdmd*) ; 
 int load_cfg_mem (struct cxd2880_tnrdmd*) ; 
 int pid_ftr_setting (struct cxd2880_tnrdmd*,struct cxd2880_tnrdmd_pid_ftr_cfg*) ; 
 int set_ts_clk_mode_and_freq (struct cxd2880_tnrdmd*,int) ; 
 int spll_reset (struct cxd2880_tnrdmd*,int) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int t_power_x (struct cxd2880_tnrdmd*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int x_tune1 (struct cxd2880_tnrdmd*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int x_tune2 (struct cxd2880_tnrdmd*,int,int,int) ; 

int cxd2880_tnrdmd_common_tune_setting1(struct cxd2880_tnrdmd *tnr_dmd,
					enum cxd2880_dtv_sys sys,
					u32 frequency_khz,
					enum cxd2880_dtv_bandwidth
					bandwidth, u8 one_seg_opt,
					u8 one_seg_opt_shft_dir)
{
	u8 data;
	enum cxd2880_tnrdmd_clockmode new_clk_mode =
				CXD2880_TNRDMD_CLOCKMODE_A;
	int shift_frequency_khz;
	u8 cpu_task_completed;
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (frequency_khz < 4000)
		return -EINVAL;

	ret = cxd2880_tnrdmd_sleep(tnr_dmd);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00,
				     0x00);
	if (ret)
		return ret;

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x2b,
				     &data,
				     1);
	if (ret)
		return ret;

	switch (sys) {
	case CXD2880_DTV_SYS_DVBT:
		if (data == 0x00) {
			ret = t_power_x(tnr_dmd, 1);
			if (ret)
				return ret;

			if (tnr_dmd->diver_mode ==
			    CXD2880_TNRDMD_DIVERMODE_MAIN) {
				ret = t_power_x(tnr_dmd->diver_sub, 1);
				if (ret)
					return ret;
			}
		}
		break;

	case CXD2880_DTV_SYS_DVBT2:
		if (data == 0x01) {
			ret = t_power_x(tnr_dmd, 0);
			if (ret)
				return ret;

			if (tnr_dmd->diver_mode ==
			    CXD2880_TNRDMD_DIVERMODE_MAIN) {
				ret = t_power_x(tnr_dmd->diver_sub, 0);
				if (ret)
					return ret;
			}
		}
		break;

	default:
		return -EINVAL;
	}

	ret = spll_reset(tnr_dmd, new_clk_mode);
	if (ret)
		return ret;

	tnr_dmd->clk_mode = new_clk_mode;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret = spll_reset(tnr_dmd->diver_sub, new_clk_mode);
		if (ret)
			return ret;

		tnr_dmd->diver_sub->clk_mode = new_clk_mode;
	}

	ret = load_cfg_mem(tnr_dmd);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret = load_cfg_mem(tnr_dmd->diver_sub);
		if (ret)
			return ret;
	}

	if (one_seg_opt) {
		if (tnr_dmd->diver_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN) {
			shift_frequency_khz = 350;
		} else {
			if (one_seg_opt_shft_dir)
				shift_frequency_khz = 350;
			else
				shift_frequency_khz = -350;

			if (tnr_dmd->create_param.xtal_share_type ==
			    CXD2880_TNRDMD_XTAL_SHARE_SLAVE)
				shift_frequency_khz *= -1;
		}
	} else {
		if (tnr_dmd->diver_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN) {
			shift_frequency_khz = 150;
		} else {
			switch (tnr_dmd->create_param.xtal_share_type) {
			case CXD2880_TNRDMD_XTAL_SHARE_NONE:
			case CXD2880_TNRDMD_XTAL_SHARE_EXTREF:
			default:
				shift_frequency_khz = 0;
				break;
			case CXD2880_TNRDMD_XTAL_SHARE_MASTER:
				shift_frequency_khz = 150;
				break;
			case CXD2880_TNRDMD_XTAL_SHARE_SLAVE:
				shift_frequency_khz = -150;
				break;
			}
		}
	}

	ret =
	    x_tune1(tnr_dmd, sys, frequency_khz, bandwidth,
		    tnr_dmd->is_cable_input, shift_frequency_khz);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret =
		    x_tune1(tnr_dmd->diver_sub, sys, frequency_khz,
			    bandwidth, tnr_dmd->is_cable_input,
			    -shift_frequency_khz);
		if (ret)
			return ret;
	}

	usleep_range(10000, 11000);

	ret =
	    cxd2880_tnrdmd_check_internal_cpu_status(tnr_dmd,
					     &cpu_task_completed);
	if (ret)
		return ret;

	if (!cpu_task_completed)
		return -EINVAL;

	ret =
	    x_tune2(tnr_dmd, bandwidth, tnr_dmd->clk_mode,
		    shift_frequency_khz);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret =
		    x_tune2(tnr_dmd->diver_sub, bandwidth,
			    tnr_dmd->diver_sub->clk_mode,
			    -shift_frequency_khz);
		if (ret)
			return ret;
	}

	if (tnr_dmd->create_param.ts_output_if == CXD2880_TNRDMD_TSOUT_IF_TS) {
		ret = set_ts_clk_mode_and_freq(tnr_dmd, sys);
	} else {
		struct cxd2880_tnrdmd_pid_ftr_cfg *pid_ftr_cfg;

		if (tnr_dmd->pid_ftr_cfg_en)
			pid_ftr_cfg = &tnr_dmd->pid_ftr_cfg;
		else
			pid_ftr_cfg = NULL;

		ret = pid_ftr_setting(tnr_dmd, pid_ftr_cfg);
	}

	return ret;
}
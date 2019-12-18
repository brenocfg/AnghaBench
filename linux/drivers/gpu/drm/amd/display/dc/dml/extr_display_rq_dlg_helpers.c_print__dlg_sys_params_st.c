#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct display_mode_lib {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  total_flip_bytes; int /*<<< orphan*/  total_flip_bw; int /*<<< orphan*/  deepsleep_dcfclk_mhz; int /*<<< orphan*/  t_srx_delay_us; int /*<<< orphan*/  t_extra_us; int /*<<< orphan*/  t_sr_wm_us; int /*<<< orphan*/  t_urg_wm_us; int /*<<< orphan*/  t_mclk_wm_us; } ;
typedef  TYPE_1__ display_dlg_sys_params_st ;

/* Variables and functions */
 int /*<<< orphan*/  dml_print (char*,...) ; 

void print__dlg_sys_params_st(struct display_mode_lib *mode_lib, display_dlg_sys_params_st dlg_sys_param)
{
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
	dml_print("DML_RQ_DLG_CALC: DISPLAY_RQ_DLG_PARAM_ST\n");
	dml_print("DML_RQ_DLG_CALC:    t_mclk_wm_us         = %3.2f\n", dlg_sys_param.t_mclk_wm_us);
	dml_print("DML_RQ_DLG_CALC:    t_urg_wm_us          = %3.2f\n", dlg_sys_param.t_urg_wm_us);
	dml_print("DML_RQ_DLG_CALC:    t_sr_wm_us           = %3.2f\n", dlg_sys_param.t_sr_wm_us);
	dml_print("DML_RQ_DLG_CALC:    t_extra_us           = %3.2f\n", dlg_sys_param.t_extra_us);
	dml_print(
			"DML_RQ_DLG_CALC:    t_srx_delay_us       = %3.2f\n",
			dlg_sys_param.t_srx_delay_us);
	dml_print(
			"DML_RQ_DLG_CALC:    deepsleep_dcfclk_mhz = %3.2f\n",
			dlg_sys_param.deepsleep_dcfclk_mhz);
	dml_print(
			"DML_RQ_DLG_CALC:    total_flip_bw        = %3.2f\n",
			dlg_sys_param.total_flip_bw);
	dml_print(
			"DML_RQ_DLG_CALC:    total_flip_bytes     = %i\n",
			dlg_sys_param.total_flip_bytes);
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
}
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
struct TYPE_3__ {int /*<<< orphan*/  qos_ramp_disable_cur1; int /*<<< orphan*/  qos_level_fixed_cur1; int /*<<< orphan*/  qos_ramp_disable_cur0; int /*<<< orphan*/  qos_level_fixed_cur0; int /*<<< orphan*/  qos_ramp_disable_c; int /*<<< orphan*/  qos_level_fixed_c; int /*<<< orphan*/  qos_ramp_disable_l; int /*<<< orphan*/  qos_level_fixed_l; int /*<<< orphan*/  refcyc_per_req_delivery_pre_cur1; int /*<<< orphan*/  refcyc_per_req_delivery_cur1; int /*<<< orphan*/  refcyc_per_req_delivery_pre_cur0; int /*<<< orphan*/  refcyc_per_req_delivery_cur0; int /*<<< orphan*/  refcyc_per_req_delivery_c; int /*<<< orphan*/  refcyc_per_req_delivery_pre_c; int /*<<< orphan*/  refcyc_per_req_delivery_l; int /*<<< orphan*/  refcyc_per_req_delivery_pre_l; int /*<<< orphan*/  qos_level_flip; int /*<<< orphan*/  min_ttu_vblank; int /*<<< orphan*/  qos_level_high_wm; int /*<<< orphan*/  qos_level_low_wm; } ;
typedef  TYPE_1__ display_ttu_regs_st ;

/* Variables and functions */
 int /*<<< orphan*/  dml_print (char*,...) ; 

void print__ttu_regs_st(struct display_mode_lib *mode_lib, display_ttu_regs_st ttu_regs)
{
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
	dml_print("DML_RQ_DLG_CALC: DISPLAY_TTU_REGS_ST\n");
	dml_print(
			"DML_RQ_DLG_CALC:    qos_level_low_wm                  = 0x%0x\n",
			ttu_regs.qos_level_low_wm);
	dml_print(
			"DML_RQ_DLG_CALC:    qos_level_high_wm                 = 0x%0x\n",
			ttu_regs.qos_level_high_wm);
	dml_print(
			"DML_RQ_DLG_CALC:    min_ttu_vblank                    = 0x%0x\n",
			ttu_regs.min_ttu_vblank);
	dml_print(
			"DML_RQ_DLG_CALC:    qos_level_flip                    = 0x%0x\n",
			ttu_regs.qos_level_flip);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_req_delivery_pre_l     = 0x%0x\n",
			ttu_regs.refcyc_per_req_delivery_pre_l);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_req_delivery_l         = 0x%0x\n",
			ttu_regs.refcyc_per_req_delivery_l);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_req_delivery_pre_c     = 0x%0x\n",
			ttu_regs.refcyc_per_req_delivery_pre_c);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_req_delivery_c         = 0x%0x\n",
			ttu_regs.refcyc_per_req_delivery_c);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_req_delivery_cur0      = 0x%0x\n",
			ttu_regs.refcyc_per_req_delivery_cur0);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_req_delivery_pre_cur0  = 0x%0x\n",
			ttu_regs.refcyc_per_req_delivery_pre_cur0);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_req_delivery_cur1      = 0x%0x\n",
			ttu_regs.refcyc_per_req_delivery_cur1);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_req_delivery_pre_cur1  = 0x%0x\n",
			ttu_regs.refcyc_per_req_delivery_pre_cur1);
	dml_print(
			"DML_RQ_DLG_CALC:    qos_level_fixed_l                 = 0x%0x\n",
			ttu_regs.qos_level_fixed_l);
	dml_print(
			"DML_RQ_DLG_CALC:    qos_ramp_disable_l                = 0x%0x\n",
			ttu_regs.qos_ramp_disable_l);
	dml_print(
			"DML_RQ_DLG_CALC:    qos_level_fixed_c                 = 0x%0x\n",
			ttu_regs.qos_level_fixed_c);
	dml_print(
			"DML_RQ_DLG_CALC:    qos_ramp_disable_c                = 0x%0x\n",
			ttu_regs.qos_ramp_disable_c);
	dml_print(
			"DML_RQ_DLG_CALC:    qos_level_fixed_cur0              = 0x%0x\n",
			ttu_regs.qos_level_fixed_cur0);
	dml_print(
			"DML_RQ_DLG_CALC:    qos_ramp_disable_cur0             = 0x%0x\n",
			ttu_regs.qos_ramp_disable_cur0);
	dml_print(
			"DML_RQ_DLG_CALC:    qos_level_fixed_cur1              = 0x%0x\n",
			ttu_regs.qos_level_fixed_cur1);
	dml_print(
			"DML_RQ_DLG_CALC:    qos_ramp_disable_cur1             = 0x%0x\n",
			ttu_regs.qos_ramp_disable_cur1);
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
}
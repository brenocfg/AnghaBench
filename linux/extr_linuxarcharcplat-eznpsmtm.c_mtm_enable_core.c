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
struct nps_host_reg_mtm_cfg {int ten; int /*<<< orphan*/  value; } ;
struct nps_host_reg_aux_mt_ctrl {int hsen; int mten; scalar_t__ value; int /*<<< orphan*/  hs_cnt; } ;
struct nps_host_reg_aux_dpc {int ien; int men; scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTOP_AUX_DPC ; 
 int /*<<< orphan*/  CTOP_AUX_MT_CTRL ; 
 int /*<<< orphan*/  MTM_CFG (unsigned int) ; 
 scalar_t__ NPS_CPU_TO_THREAD_NUM (unsigned int) ; 
 int NPS_NUM_HW_THREADS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtm_hs_ctr ; 
 int /*<<< orphan*/  mtm_init_nat (unsigned int) ; 
 int /*<<< orphan*/  mtm_init_thread (unsigned int) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,scalar_t__) ; 

void mtm_enable_core(unsigned int cpu)
{
	int i;
	struct nps_host_reg_aux_mt_ctrl mt_ctrl;
	struct nps_host_reg_mtm_cfg mtm_cfg;
	struct nps_host_reg_aux_dpc dpc;

	/*
	 * Initializing dpc register in each CPU.
	 * Overwriting the init value of the DPC
	 * register so that CMEM and FMT virtual address
	 * spaces are accessible, and Data Plane HW
	 * facilities are enabled.
	 */
	dpc.ien = 1;
	dpc.men = 1;
	write_aux_reg(CTOP_AUX_DPC, dpc.value);

	if (NPS_CPU_TO_THREAD_NUM(cpu) != 0)
		return;

	/* Initialize Number of Active Threads */
	mtm_init_nat(cpu);

	/* Initialize mtm_cfg */
	mtm_cfg.value = ioread32be(MTM_CFG(cpu));
	mtm_cfg.ten = 1;
	iowrite32be(mtm_cfg.value, MTM_CFG(cpu));

	/* Initialize all other threads in core */
	for (i = 1; i < NPS_NUM_HW_THREADS; i++)
		mtm_init_thread(cpu + i);


	/* Enable HW schedule, stall counter, mtm */
	mt_ctrl.value = 0;
	mt_ctrl.hsen = 1;
	mt_ctrl.hs_cnt = mtm_hs_ctr;
	mt_ctrl.mten = 1;
	write_aux_reg(CTOP_AUX_MT_CTRL, mt_ctrl.value);

	/*
	 * HW scheduling mechanism will start working
	 * Only after call to instruction "schd.rw".
	 * cpu_relax() calls "schd.rw" instruction.
	 */
	cpu_relax();
}
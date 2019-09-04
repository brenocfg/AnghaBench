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
struct nps_host_reg_mtm_cfg {int nat; int /*<<< orphan*/  value; } ;
struct nps_host_reg_aux_udmc {int nat; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTOP_AUX_UDMC ; 
 int /*<<< orphan*/  MTM_CFG (int) ; 
 int NPS_NUM_HW_THREADS ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_bits (int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_aux_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtm_init_nat(int cpu)
{
	struct nps_host_reg_mtm_cfg mtm_cfg;
	struct nps_host_reg_aux_udmc udmc;
	int log_nat, nat = 0, i, t;

	/* Iterate core threads and update nat */
	for (i = 0, t = cpu; i < NPS_NUM_HW_THREADS; i++, t++)
		nat += test_bit(t, cpumask_bits(cpu_possible_mask));

	log_nat = ilog2(nat);

	udmc.value = read_aux_reg(CTOP_AUX_UDMC);
	udmc.nat = log_nat;
	write_aux_reg(CTOP_AUX_UDMC, udmc.value);

	mtm_cfg.value = ioread32be(MTM_CFG(cpu));
	mtm_cfg.nat = log_nat;
	iowrite32be(mtm_cfg.value, MTM_CFG(cpu));
}
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

/* Variables and functions */
 int /*<<< orphan*/  MTM_CFG (int) ; 
 int NPS_CPU_TO_THREAD_NUM (int) ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mtm_enable_thread(int cpu)
{
	struct nps_host_reg_mtm_cfg mtm_cfg;

	if (NPS_CPU_TO_THREAD_NUM(cpu) == 0)
		return 1;

	/* Enable thread in mtm */
	mtm_cfg.value = ioread32be(MTM_CFG(cpu));
	mtm_cfg.ten |= (1 << (NPS_CPU_TO_THREAD_NUM(cpu)));
	iowrite32be(mtm_cfg.value, MTM_CFG(cpu));

	return 0;
}
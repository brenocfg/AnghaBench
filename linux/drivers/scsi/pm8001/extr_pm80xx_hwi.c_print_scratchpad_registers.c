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
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGU_HOST_SCRATCH_PAD_0 ; 
 int /*<<< orphan*/  MSGU_HOST_SCRATCH_PAD_1 ; 
 int /*<<< orphan*/  MSGU_HOST_SCRATCH_PAD_2 ; 
 int /*<<< orphan*/  MSGU_HOST_SCRATCH_PAD_3 ; 
 int /*<<< orphan*/  MSGU_HOST_SCRATCH_PAD_4 ; 
 int /*<<< orphan*/  MSGU_HOST_SCRATCH_PAD_5 ; 
 int /*<<< orphan*/  MSGU_HOST_SCRATCH_PAD_6 ; 
 int /*<<< orphan*/  MSGU_HOST_SCRATCH_PAD_7 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_0 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_1 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_2 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_3 ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_cr32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_scratchpad_registers(struct pm8001_hba_info *pm8001_ha)
{
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_SCRATCH_PAD_0: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_SCRATCH_PAD_1:0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_SCRATCH_PAD_2: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_SCRATCH_PAD_3: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_3)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_HOST_SCRATCH_PAD_0: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_0)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_HOST_SCRATCH_PAD_1: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_1)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_HOST_SCRATCH_PAD_2: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_2)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_HOST_SCRATCH_PAD_3: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_3)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_HOST_SCRATCH_PAD_4: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_4)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_HOST_SCRATCH_PAD_5: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_5)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_RSVD_SCRATCH_PAD_0: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_6)));
	PM8001_FAIL_DBG(pm8001_ha,
		pm8001_printk("MSGU_RSVD_SCRATCH_PAD_1: 0x%x\n",
			pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_7)));
}
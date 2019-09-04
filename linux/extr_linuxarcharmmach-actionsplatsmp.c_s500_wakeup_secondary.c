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

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OWL_CPU1_ADDR ; 
 scalar_t__ OWL_CPU1_FLAG ; 
 int /*<<< orphan*/  OWL_CPUx_FLAG_BOOT ; 
 int /*<<< orphan*/  OWL_SPS_PG_CTL_ACK_CPU2 ; 
 int /*<<< orphan*/  OWL_SPS_PG_CTL_ACK_CPU3 ; 
 int /*<<< orphan*/  OWL_SPS_PG_CTL_PWR_CPU2 ; 
 int /*<<< orphan*/  OWL_SPS_PG_CTL_PWR_CPU3 ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsb_sev () ; 
 int /*<<< orphan*/  mb () ; 
 int owl_sps_set_pg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secondary_startup ; 
 int /*<<< orphan*/  sps_base_addr ; 
 scalar_t__ timer_base_addr ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s500_wakeup_secondary(unsigned int cpu)
{
	int ret;

	if (cpu > 3)
		return -EINVAL;

	/* The generic PM domain driver is not available this early. */
	switch (cpu) {
	case 2:
		ret = owl_sps_set_pg(sps_base_addr,
		                     OWL_SPS_PG_CTL_PWR_CPU2,
				     OWL_SPS_PG_CTL_ACK_CPU2, true);
		if (ret)
			return ret;
		break;
	case 3:
		ret = owl_sps_set_pg(sps_base_addr,
		                     OWL_SPS_PG_CTL_PWR_CPU3,
				     OWL_SPS_PG_CTL_ACK_CPU3, true);
		if (ret)
			return ret;
		break;
	}

	/* wait for CPUx to run to WFE instruction */
	udelay(200);

	writel(__pa_symbol(secondary_startup),
	       timer_base_addr + OWL_CPU1_ADDR + (cpu - 1) * 4);
	writel(OWL_CPUx_FLAG_BOOT,
	       timer_base_addr + OWL_CPU1_FLAG + (cpu - 1) * 4);

	dsb_sev();
	mb();

	return 0;
}
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
struct lima_ip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_PMU_INT_MASK ; 
 int /*<<< orphan*/  LIMA_PMU_POWER_UP ; 
 int /*<<< orphan*/  LIMA_PMU_STATUS ; 
 int /*<<< orphan*/  LIMA_PMU_SW_DELAY ; 
 int lima_pmu_wait_cmd (struct lima_ip*) ; 
 int pmu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_write (int /*<<< orphan*/ ,int) ; 

int lima_pmu_init(struct lima_ip *ip)
{
	int err;
	u32 stat;

	pmu_write(LIMA_PMU_INT_MASK, 0);

	/* If this value is too low, when in high GPU clk freq,
	 * GPU will be in unstable state.
	 */
	pmu_write(LIMA_PMU_SW_DELAY, 0xffff);

	/* status reg 1=off 0=on */
	stat = pmu_read(LIMA_PMU_STATUS);

	/* power up all ip */
	if (stat) {
		pmu_write(LIMA_PMU_POWER_UP, stat);
		err = lima_pmu_wait_cmd(ip);
		if (err)
			return err;
	}
	return 0;
}
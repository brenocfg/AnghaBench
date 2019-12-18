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
struct ssb_chipcommon {int dummy; } ;
struct pmu0_plltab_entry {int freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SSB_CHIPCO_PMU_CTL ; 
 int SSB_CHIPCO_PMU_CTL_XTALFREQ ; 
 int SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT ; 
 int chipco_read32 (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 
 struct pmu0_plltab_entry* pmu0_plltab_find_entry (int) ; 

__attribute__((used)) static u32 ssb_pmu_get_alp_clock_clk0(struct ssb_chipcommon *cc)
{
	u32 crystalfreq;
	const struct pmu0_plltab_entry *e = NULL;

	crystalfreq = (chipco_read32(cc, SSB_CHIPCO_PMU_CTL) &
		       SSB_CHIPCO_PMU_CTL_XTALFREQ)  >> SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT;
	e = pmu0_plltab_find_entry(crystalfreq);
	BUG_ON(!e);
	return e->freq * 1000;
}
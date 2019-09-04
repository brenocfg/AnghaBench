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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int MAX_ALT ; 
 unsigned int PPMU_LIMITED_PMC_OK ; 
 unsigned int PPMU_LIMITED_PMC_REQD ; 
 unsigned int PPMU_ONLY_COUNT_RUN ; 
 scalar_t__** event_alternatives ; 
 int find_alternative (scalar_t__) ; 
 scalar_t__ find_alternative_bdecode (scalar_t__) ; 
 int power5p_limited_pmc_event (scalar_t__) ; 

__attribute__((used)) static int power5p_get_alternatives(u64 event, unsigned int flags, u64 alt[])
{
	int i, j, nalt = 1;
	int nlim;
	s64 ae;

	alt[0] = event;
	nalt = 1;
	nlim = power5p_limited_pmc_event(event);
	i = find_alternative(event);
	if (i >= 0) {
		for (j = 0; j < MAX_ALT; ++j) {
			ae = event_alternatives[i][j];
			if (ae && ae != event)
				alt[nalt++] = ae;
			nlim += power5p_limited_pmc_event(ae);
		}
	} else {
		ae = find_alternative_bdecode(event);
		if (ae > 0)
			alt[nalt++] = ae;
	}

	if (flags & PPMU_ONLY_COUNT_RUN) {
		/*
		 * We're only counting in RUN state,
		 * so PM_CYC is equivalent to PM_RUN_CYC
		 * and PM_INST_CMPL === PM_RUN_INST_CMPL.
		 * This doesn't include alternatives that don't provide
		 * any extra flexibility in assigning PMCs (e.g.
		 * 0x100005 for PM_RUN_CYC vs. 0xf for PM_CYC).
		 * Note that even with these additional alternatives
		 * we never end up with more than 3 alternatives for any event.
		 */
		j = nalt;
		for (i = 0; i < nalt; ++i) {
			switch (alt[i]) {
			case 0xf:	/* PM_CYC */
				alt[j++] = 0x600005;	/* PM_RUN_CYC */
				++nlim;
				break;
			case 0x600005:	/* PM_RUN_CYC */
				alt[j++] = 0xf;
				break;
			case 0x100009:	/* PM_INST_CMPL */
				alt[j++] = 0x500009;	/* PM_RUN_INST_CMPL */
				++nlim;
				break;
			case 0x500009:	/* PM_RUN_INST_CMPL */
				alt[j++] = 0x100009;	/* PM_INST_CMPL */
				alt[j++] = 0x200009;
				break;
			}
		}
		nalt = j;
	}

	if (!(flags & PPMU_LIMITED_PMC_OK) && nlim) {
		/* remove the limited PMC events */
		j = 0;
		for (i = 0; i < nalt; ++i) {
			if (!power5p_limited_pmc_event(alt[i])) {
				alt[j] = alt[i];
				++j;
			}
		}
		nalt = j;
	} else if ((flags & PPMU_LIMITED_PMC_REQD) && nlim < nalt) {
		/* remove all but the limited PMC events */
		j = 0;
		for (i = 0; i < nalt; ++i) {
			if (power5p_limited_pmc_event(alt[i])) {
				alt[j] = alt[i];
				++j;
			}
		}
		nalt = j;
	}

	return nalt;
}
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
 unsigned int PPMU_ONLY_COUNT_RUN ; 
 scalar_t__** event_alternatives ; 
 int find_alternative (scalar_t__) ; 
 scalar_t__ find_alternative_decode (scalar_t__) ; 

__attribute__((used)) static int power7_get_alternatives(u64 event, unsigned int flags, u64 alt[])
{
	int i, j, nalt = 1;
	s64 ae;

	alt[0] = event;
	nalt = 1;
	i = find_alternative(event);
	if (i >= 0) {
		for (j = 0; j < MAX_ALT; ++j) {
			ae = event_alternatives[i][j];
			if (ae && ae != event)
				alt[nalt++] = ae;
		}
	} else {
		ae = find_alternative_decode(event);
		if (ae > 0)
			alt[nalt++] = ae;
	}

	if (flags & PPMU_ONLY_COUNT_RUN) {
		/*
		 * We're only counting in RUN state,
		 * so PM_CYC is equivalent to PM_RUN_CYC
		 * and PM_INST_CMPL === PM_RUN_INST_CMPL.
		 * This doesn't include alternatives that don't provide
		 * any extra flexibility in assigning PMCs.
		 */
		j = nalt;
		for (i = 0; i < nalt; ++i) {
			switch (alt[i]) {
			case 0x1e:	/* PM_CYC */
				alt[j++] = 0x600f4;	/* PM_RUN_CYC */
				break;
			case 0x600f4:	/* PM_RUN_CYC */
				alt[j++] = 0x1e;
				break;
			case 0x2:	/* PM_PPC_CMPL */
				alt[j++] = 0x500fa;	/* PM_RUN_INST_CMPL */
				break;
			case 0x500fa:	/* PM_RUN_INST_CMPL */
				alt[j++] = 0x2;	/* PM_PPC_CMPL */
				break;
			}
		}
		nalt = j;
	}

	return nalt;
}
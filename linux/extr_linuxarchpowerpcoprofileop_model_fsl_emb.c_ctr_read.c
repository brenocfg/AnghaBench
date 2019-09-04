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
 int /*<<< orphan*/  PMRN_PMC0 ; 
 int /*<<< orphan*/  PMRN_PMC1 ; 
 int /*<<< orphan*/  PMRN_PMC2 ; 
 int /*<<< orphan*/  PMRN_PMC3 ; 
 int /*<<< orphan*/  PMRN_PMC4 ; 
 int /*<<< orphan*/  PMRN_PMC5 ; 
 unsigned int mfpmr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int ctr_read(unsigned int i)
{
	switch(i) {
		case 0:
			return mfpmr(PMRN_PMC0);
		case 1:
			return mfpmr(PMRN_PMC1);
		case 2:
			return mfpmr(PMRN_PMC2);
		case 3:
			return mfpmr(PMRN_PMC3);
		case 4:
			return mfpmr(PMRN_PMC4);
		case 5:
			return mfpmr(PMRN_PMC5);
		default:
			return 0;
	}
}
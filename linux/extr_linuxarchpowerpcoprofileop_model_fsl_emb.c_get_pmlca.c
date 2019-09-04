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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PMRN_PMLCA0 ; 
 int /*<<< orphan*/  PMRN_PMLCA1 ; 
 int /*<<< orphan*/  PMRN_PMLCA2 ; 
 int /*<<< orphan*/  PMRN_PMLCA3 ; 
 int /*<<< orphan*/  PMRN_PMLCA4 ; 
 int /*<<< orphan*/  PMRN_PMLCA5 ; 
 int /*<<< orphan*/  mfpmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static inline u32 get_pmlca(int ctr)
{
	u32 pmlca;

	switch (ctr) {
		case 0:
			pmlca = mfpmr(PMRN_PMLCA0);
			break;
		case 1:
			pmlca = mfpmr(PMRN_PMLCA1);
			break;
		case 2:
			pmlca = mfpmr(PMRN_PMLCA2);
			break;
		case 3:
			pmlca = mfpmr(PMRN_PMLCA3);
			break;
		case 4:
			pmlca = mfpmr(PMRN_PMLCA4);
			break;
		case 5:
			pmlca = mfpmr(PMRN_PMLCA5);
			break;
		default:
			panic("Bad ctr number\n");
	}

	return pmlca;
}
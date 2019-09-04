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
struct unwind_table {int dummy; } ;

/* Variables and functions */
 int const CIE_ID ; 
 int* __cie_for_fde (int const*) ; 
 int const bad_cie ; 
 int const not_fde ; 

__attribute__((used)) static const u32 *cie_for_fde(const u32 *fde, const struct unwind_table *table)
{
	const u32 *cie;

	if (!*fde || (*fde & (sizeof(*fde) - 1)))
		return &bad_cie;

	if (fde[1] == CIE_ID)
		return &not_fde;	/* this is a CIE */

	if ((fde[1] & (sizeof(*fde) - 1)))
/* || fde[1] > (unsigned long)(fde + 1) - (unsigned long)table->address) */
		return NULL;	/* this is not a valid FDE */

	cie = __cie_for_fde(fde);

	if (*cie <= sizeof(*cie) + 4 || *cie >= fde[1] - sizeof(*fde)
	    || (*cie & (sizeof(*cie) - 1))
	    || (cie[1] != CIE_ID))
		return NULL;	/* this is not a (valid) CIE */
	return cie;
}
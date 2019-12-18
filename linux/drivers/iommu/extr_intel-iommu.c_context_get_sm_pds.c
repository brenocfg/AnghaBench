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
struct pasid_table {int max_pasid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NR_PASID_BITS ; 
 int PASID_PDE_SHIFT ; 
 int find_first_bit (unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long context_get_sm_pds(struct pasid_table *table)
{
	int pds, max_pde;

	max_pde = table->max_pasid >> PASID_PDE_SHIFT;
	pds = find_first_bit((unsigned long *)&max_pde, MAX_NR_PASID_BITS);
	if (pds < 7)
		return 0;

	return pds - 7;
}
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
struct copro_slb {unsigned long esid; } ;

/* Variables and functions */
 unsigned long ESID_MASK ; 

__attribute__((used)) static inline int __slb_present(struct copro_slb *slbs, int nr_slbs,
		void *new_addr)
{
	unsigned long ea = (unsigned long)new_addr;
	int i;

	for (i = 0; i < nr_slbs; i++)
		if (!((slbs[i].esid ^ ea) & ESID_MASK))
			return 1;

	return 0;
}
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
typedef  int /*<<< orphan*/  u64 ;
struct ce_array {int n; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 unsigned int FULL_COUNT (int /*<<< orphan*/ ) ; 
 unsigned int FULL_COUNT_MASK ; 
 int /*<<< orphan*/  PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_elem (struct ce_array*,int) ; 

__attribute__((used)) static u64 del_lru_elem_unlocked(struct ce_array *ca)
{
	unsigned int min = FULL_COUNT_MASK;
	int i, min_idx = 0;

	for (i = 0; i < ca->n; i++) {
		unsigned int this = FULL_COUNT(ca->array[i]);

		if (min > this) {
			min = this;
			min_idx = i;
		}
	}

	del_elem(ca, min_idx);

	return PFN(ca->array[min_idx]);
}
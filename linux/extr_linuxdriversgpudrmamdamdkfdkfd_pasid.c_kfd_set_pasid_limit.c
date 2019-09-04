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
 scalar_t__ kfd2kgd ; 
 unsigned int pasid_bits ; 

bool kfd_set_pasid_limit(unsigned int new_limit)
{
	if (new_limit < 2)
		return false;

	if (new_limit < (1U << pasid_bits)) {
		if (kfd2kgd)
			/* We've already allocated user PASIDs, too late to
			 * change the limit
			 */
			return false;

		while (new_limit < (1U << pasid_bits))
			pasid_bits--;
	}

	return true;
}
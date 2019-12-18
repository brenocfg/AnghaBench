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
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int mec_emi_base ; 
 unsigned int mec_emi_end ; 

int cros_ec_lpc_mec_in_range(unsigned int offset, unsigned int length)
{
	if (length == 0)
		return -EINVAL;

	if (WARN_ON(mec_emi_base == 0 || mec_emi_end == 0))
		return -EINVAL;

	if (offset >= mec_emi_base && offset < mec_emi_end) {
		if (WARN_ON(offset + length - 1 >= mec_emi_end))
			return -EINVAL;
		return 1;
	}

	if (WARN_ON(offset + length > mec_emi_base && offset < mec_emi_end))
		return -EINVAL;

	return 0;
}
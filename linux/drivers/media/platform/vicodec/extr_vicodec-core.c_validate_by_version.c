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
 unsigned int FWHT_FL_COMPONENTS_NUM_MSK ; 
 unsigned int FWHT_FL_COMPONENTS_NUM_OFFSET ; 
 unsigned int FWHT_FL_PIXENC_MSK ; 
 unsigned int FWHT_VERSION ; 

__attribute__((used)) static bool validate_by_version(unsigned int flags, unsigned int version)
{
	if (!version || version > FWHT_VERSION)
		return false;

	if (version >= 2) {
		unsigned int components_num = 1 +
			((flags & FWHT_FL_COMPONENTS_NUM_MSK) >>
			 FWHT_FL_COMPONENTS_NUM_OFFSET);
		unsigned int pixenc = flags & FWHT_FL_PIXENC_MSK;

		if (components_num == 0 || components_num > 4 || !pixenc)
			return false;
	}
	return true;
}
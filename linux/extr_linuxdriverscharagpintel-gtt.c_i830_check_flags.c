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
#define  AGP_PHYS_MEMORY 130 
#define  AGP_USER_CACHED_MEMORY 129 
#define  AGP_USER_MEMORY 128 

__attribute__((used)) static bool i830_check_flags(unsigned int flags)
{
	switch (flags) {
	case 0:
	case AGP_PHYS_MEMORY:
	case AGP_USER_CACHED_MEMORY:
	case AGP_USER_MEMORY:
		return true;
	}

	return false;
}
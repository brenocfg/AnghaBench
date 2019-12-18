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
 int EIO ; 
 int ENXIO ; 

int dell_smbios_error(int value)
{
	switch (value) {
	case 0: /* Completed successfully */
		return 0;
	case -1: /* Completed with error */
		return -EIO;
	case -2: /* Function not supported */
		return -ENXIO;
	default: /* Unknown error */
		return -EINVAL;
	}
}
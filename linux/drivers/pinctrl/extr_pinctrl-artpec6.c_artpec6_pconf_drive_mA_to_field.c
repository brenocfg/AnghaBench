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
#define  ARTPEC6_DRIVE_4mA 131 
 int ARTPEC6_DRIVE_4mA_SET ; 
#define  ARTPEC6_DRIVE_6mA 130 
 int ARTPEC6_DRIVE_6mA_SET ; 
#define  ARTPEC6_DRIVE_8mA 129 
 int ARTPEC6_DRIVE_8mA_SET ; 
#define  ARTPEC6_DRIVE_9mA 128 
 int ARTPEC6_DRIVE_9mA_SET ; 
 int EINVAL ; 

__attribute__((used)) static int artpec6_pconf_drive_mA_to_field(unsigned int mA)
{
	switch (mA) {
	case ARTPEC6_DRIVE_4mA:
		return ARTPEC6_DRIVE_4mA_SET;
	case ARTPEC6_DRIVE_6mA:
		return ARTPEC6_DRIVE_6mA_SET;
	case ARTPEC6_DRIVE_8mA:
		return ARTPEC6_DRIVE_8mA_SET;
	case ARTPEC6_DRIVE_9mA:
		return ARTPEC6_DRIVE_9mA_SET;
	default:
		return -EINVAL;
	}
}
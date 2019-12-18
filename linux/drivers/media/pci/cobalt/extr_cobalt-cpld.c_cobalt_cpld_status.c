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
struct cobalt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cobalt_info (char*,int) ; 
 int /*<<< orphan*/  cpld_info_ver3 (struct cobalt*) ; 
 int cpld_read (struct cobalt*,int) ; 

void cobalt_cpld_status(struct cobalt *cobalt)
{
	u32 rev = cpld_read(cobalt, 0x30);

	switch (rev) {
	case 3:
	case 4:
	case 5:
		cpld_info_ver3(cobalt);
		break;
	default:
		cobalt_info("CPLD revision %u is not supported!\n", rev);
		break;
	}
}
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
typedef  int u64 ;

/* Variables and functions */
 int ACPI_100NSEC_PER_SEC ; 
 int HZ ; 
 int INITIAL_JIFFIES ; 
 int get_jiffies_64 () ; 

u64 acpi_os_get_timer(void)
{
	return (get_jiffies_64() - INITIAL_JIFFIES) *
		(ACPI_100NSEC_PER_SEC / HZ);
}
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
 int /*<<< orphan*/  phys_cpu_present_map ; 
 int physid_isset (int,int /*<<< orphan*/ ) ; 

int default_check_phys_apicid_present(int phys_apicid)
{
	return physid_isset(phys_apicid, phys_cpu_present_map);
}
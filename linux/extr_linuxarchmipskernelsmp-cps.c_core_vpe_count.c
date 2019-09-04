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
 int mips_cps_numvps (unsigned int,unsigned int) ; 
 scalar_t__ threads_disabled ; 

__attribute__((used)) static unsigned core_vpe_count(unsigned int cluster, unsigned core)
{
	if (threads_disabled)
		return 1;

	return mips_cps_numvps(cluster, core);
}
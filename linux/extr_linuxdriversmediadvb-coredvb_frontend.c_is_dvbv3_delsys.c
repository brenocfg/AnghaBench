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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ SYS_ATSC ; 
 scalar_t__ SYS_DVBC_ANNEX_A ; 
 scalar_t__ SYS_DVBS ; 
 scalar_t__ SYS_DVBT ; 

__attribute__((used)) static bool is_dvbv3_delsys(u32 delsys)
{
	return (delsys == SYS_DVBT) || (delsys == SYS_DVBC_ANNEX_A) ||
	       (delsys == SYS_DVBS) || (delsys == SYS_ATSC);
}
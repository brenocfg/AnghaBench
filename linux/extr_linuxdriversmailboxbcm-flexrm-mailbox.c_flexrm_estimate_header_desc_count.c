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

/* Variables and functions */
 int HEADER_BDCOUNT_MAX ; 

__attribute__((used)) static u32 flexrm_estimate_header_desc_count(u32 nhcnt)
{
	u32 hcnt = nhcnt / HEADER_BDCOUNT_MAX;

	if (!(nhcnt % HEADER_BDCOUNT_MAX))
		hcnt += 1;

	return hcnt;
}
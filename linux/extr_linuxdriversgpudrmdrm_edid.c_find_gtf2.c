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
typedef  int u8 ;
struct detailed_timing {int dummy; } ;

/* Variables and functions */
 int EDID_DETAIL_MONITOR_RANGE ; 

__attribute__((used)) static void
find_gtf2(struct detailed_timing *t, void *data)
{
	u8 *r = (u8 *)t;
	if (r[3] == EDID_DETAIL_MONITOR_RANGE && r[10] == 0x02)
		*(u8 **)data = r;
}
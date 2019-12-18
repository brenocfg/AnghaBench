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
struct rvt_mregion {scalar_t__ lkey; } ;

/* Variables and functions */

bool rvt_mr_has_lkey(struct rvt_mregion *mr, u32 lkey)
{
	return mr && lkey == mr->lkey;
}
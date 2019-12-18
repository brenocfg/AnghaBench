#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resync_info {void* hi; void* lo; } ;
struct TYPE_2__ {scalar_t__ sb_lvbptr; } ;
struct dlm_lock_resource {TYPE_1__ lksb; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_resync_info(struct dlm_lock_resource *lockres,
			    sector_t lo, sector_t hi)
{
	struct resync_info *ri;

	ri = (struct resync_info *)lockres->lksb.sb_lvbptr;
	ri->lo = cpu_to_le64(lo);
	ri->hi = cpu_to_le64(hi);
}
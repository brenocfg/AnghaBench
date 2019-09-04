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
struct slb_shadow {TYPE_1__* save_area; } ;
typedef  enum slb_index { ____Placeholder_slb_index } slb_index ;
struct TYPE_2__ {int /*<<< orphan*/  esid; int /*<<< orphan*/  vsid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct slb_shadow* get_slb_shadow () ; 
 int /*<<< orphan*/  mk_esid_data (unsigned long,int,int) ; 
 int /*<<< orphan*/  mk_vsid_data (unsigned long,int,unsigned long) ; 

__attribute__((used)) static inline void slb_shadow_update(unsigned long ea, int ssize,
				     unsigned long flags,
				     enum slb_index index)
{
	struct slb_shadow *p = get_slb_shadow();

	/*
	 * Clear the ESID first so the entry is not valid while we are
	 * updating it.  No write barriers are needed here, provided
	 * we only update the current CPU's SLB shadow buffer.
	 */
	WRITE_ONCE(p->save_area[index].esid, 0);
	WRITE_ONCE(p->save_area[index].vsid, cpu_to_be64(mk_vsid_data(ea, ssize, flags)));
	WRITE_ONCE(p->save_area[index].esid, cpu_to_be64(mk_esid_data(ea, ssize, index)));
}
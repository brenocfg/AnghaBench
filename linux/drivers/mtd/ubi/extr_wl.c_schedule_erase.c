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
struct ubi_work {int vol_id; int lnum; int torture; struct ubi_wl_entry* e; int /*<<< orphan*/ * func; } ;
struct ubi_wl_entry {int /*<<< orphan*/  ec; int /*<<< orphan*/  pnum; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  __schedule_ubi_work (struct ubi_device*,struct ubi_work*) ; 
 int /*<<< orphan*/  dbg_wl (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  erase_worker ; 
 struct ubi_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_ubi_work (struct ubi_device*,struct ubi_work*) ; 
 int /*<<< orphan*/  ubi_assert (struct ubi_wl_entry*) ; 

__attribute__((used)) static int schedule_erase(struct ubi_device *ubi, struct ubi_wl_entry *e,
			  int vol_id, int lnum, int torture, bool nested)
{
	struct ubi_work *wl_wrk;

	ubi_assert(e);

	dbg_wl("schedule erasure of PEB %d, EC %d, torture %d",
	       e->pnum, e->ec, torture);

	wl_wrk = kmalloc(sizeof(struct ubi_work), GFP_NOFS);
	if (!wl_wrk)
		return -ENOMEM;

	wl_wrk->func = &erase_worker;
	wl_wrk->e = e;
	wl_wrk->vol_id = vol_id;
	wl_wrk->lnum = lnum;
	wl_wrk->torture = torture;

	if (nested)
		__schedule_ubi_work(ubi, wl_wrk);
	else
		schedule_ubi_work(ubi, wl_wrk);
	return 0;
}
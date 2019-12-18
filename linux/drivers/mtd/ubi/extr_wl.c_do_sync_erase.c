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
struct ubi_work {int vol_id; int lnum; int torture; struct ubi_wl_entry* e; } ;
struct ubi_wl_entry {int /*<<< orphan*/  pnum; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int __erase_worker (struct ubi_device*,struct ubi_work*) ; 
 int /*<<< orphan*/  dbg_wl (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_sync_erase(struct ubi_device *ubi, struct ubi_wl_entry *e,
			 int vol_id, int lnum, int torture)
{
	struct ubi_work wl_wrk;

	dbg_wl("sync erase of PEB %i", e->pnum);

	wl_wrk.e = e;
	wl_wrk.vol_id = vol_id;
	wl_wrk.lnum = lnum;
	wl_wrk.torture = torture;

	return __erase_worker(ubi, &wl_wrk);
}
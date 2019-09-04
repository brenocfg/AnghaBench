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
struct ubi_work {struct ubi_wl_entry* e; } ;
struct ubi_wl_entry {int /*<<< orphan*/  ec; int /*<<< orphan*/  pnum; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int __erase_worker (struct ubi_device*,struct ubi_work*) ; 
 int /*<<< orphan*/  dbg_wl (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ubi_work*) ; 
 int /*<<< orphan*/  wl_entry_destroy (struct ubi_device*,struct ubi_wl_entry*) ; 

__attribute__((used)) static int erase_worker(struct ubi_device *ubi, struct ubi_work *wl_wrk,
			  int shutdown)
{
	int ret;

	if (shutdown) {
		struct ubi_wl_entry *e = wl_wrk->e;

		dbg_wl("cancel erasure of PEB %d EC %d", e->pnum, e->ec);
		kfree(wl_wrk);
		wl_entry_destroy(ubi, e);
		return 0;
	}

	ret = __erase_worker(ubi, wl_wrk);
	kfree(wl_wrk);
	return ret;
}
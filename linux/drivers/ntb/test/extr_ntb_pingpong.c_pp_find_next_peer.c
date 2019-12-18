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
typedef  int u64 ;
struct pp_ctx {int nmask; int pmask; int out_pidx; int out_db; int /*<<< orphan*/  lock; int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int ENODEV ; 
 int __ffs64 (int) ; 
 int ntb_link_is_up (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pp_find_next_peer(struct pp_ctx *pp)
{
	u64 link, out_db;
	int pidx;

	link = ntb_link_is_up(pp->ntb, NULL, NULL);

	/* Find next available peer */
	if (link & pp->nmask) {
		pidx = __ffs64(link & pp->nmask);
		out_db = BIT_ULL(pidx + 1);
	} else if (link & pp->pmask) {
		pidx = __ffs64(link & pp->pmask);
		out_db = BIT_ULL(pidx);
	} else {
		return -ENODEV;
	}

	spin_lock(&pp->lock);
	pp->out_pidx = pidx;
	pp->out_db = out_db;
	spin_unlock(&pp->lock);

	return 0;
}
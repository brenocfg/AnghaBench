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
struct fc_exch_mgr {int /*<<< orphan*/  ep_pool; } ;
struct fc_exch {int esb_stat; int /*<<< orphan*/  arg; int /*<<< orphan*/  seq; int /*<<< orphan*/  (* destructor ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;struct fc_exch_mgr* em; int /*<<< orphan*/  ex_refcnt; } ;

/* Variables and functions */
 int ESB_ST_COMPLETE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_free (struct fc_exch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_exch_release(struct fc_exch *ep)
{
	struct fc_exch_mgr *mp;

	if (atomic_dec_and_test(&ep->ex_refcnt)) {
		mp = ep->em;
		if (ep->destructor)
			ep->destructor(&ep->seq, ep->arg);
		WARN_ON(!(ep->esb_stat & ESB_ST_COMPLETE));
		mempool_free(ep, mp->ep_pool);
	}
}
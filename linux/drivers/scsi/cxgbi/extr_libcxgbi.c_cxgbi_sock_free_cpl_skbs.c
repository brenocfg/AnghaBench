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
struct cxgbi_sock {int /*<<< orphan*/ * cpl_abort_rpl; int /*<<< orphan*/ * cpl_abort_req; int /*<<< orphan*/ * cpl_close; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 

void cxgbi_sock_free_cpl_skbs(struct cxgbi_sock *csk)
{
	if (csk->cpl_close) {
		kfree_skb(csk->cpl_close);
		csk->cpl_close = NULL;
	}
	if (csk->cpl_abort_req) {
		kfree_skb(csk->cpl_abort_req);
		csk->cpl_abort_req = NULL;
	}
	if (csk->cpl_abort_rpl) {
		kfree_skb(csk->cpl_abort_rpl);
		csk->cpl_abort_rpl = NULL;
	}
}
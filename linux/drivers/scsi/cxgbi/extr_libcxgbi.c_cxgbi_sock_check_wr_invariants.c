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
struct cxgbi_sock {scalar_t__ wr_max_cred; scalar_t__ wr_cred; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int cxgbi_sock_count_pending_wrs (struct cxgbi_sock const*) ; 
 int /*<<< orphan*/  pr_err (char*,struct cxgbi_sock const*,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

void cxgbi_sock_check_wr_invariants(const struct cxgbi_sock *csk)
{
	int pending = cxgbi_sock_count_pending_wrs(csk);

	if (unlikely(csk->wr_cred + pending != csk->wr_max_cred))
		pr_err("csk 0x%p, tid %u, credit %u + %u != %u.\n",
			csk, csk->tid, csk->wr_cred, pending, csk->wr_max_cred);
}
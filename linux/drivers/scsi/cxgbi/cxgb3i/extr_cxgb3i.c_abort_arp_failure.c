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
struct t3cdev {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cpl_abort_req {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_ABORT_NO_RST ; 
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 int /*<<< orphan*/  GET_TID (struct cpl_abort_req*) ; 
 struct cpl_abort_req* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgb3_ofld_send (struct t3cdev*,struct sk_buff*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct t3cdev*,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void abort_arp_failure(struct t3cdev *tdev, struct sk_buff *skb)
{
	struct cpl_abort_req *req = cplhdr(skb);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"t3dev 0x%p, tid %u, skb 0x%p.\n",
		tdev, GET_TID(req), skb);
	req->cmd = CPL_ABORT_NO_RST;
	cxgb3_ofld_send(tdev, skb);
}
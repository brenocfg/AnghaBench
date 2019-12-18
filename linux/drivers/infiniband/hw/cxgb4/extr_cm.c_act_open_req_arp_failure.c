#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; } ;
struct sk_buff {int dummy; } ;
struct TYPE_7__ {scalar_t__ ss_family; } ;
struct TYPE_12__ {TYPE_5__* dev; int /*<<< orphan*/  local_addr; TYPE_1__ remote_addr; } ;
struct c4iw_ep {int /*<<< orphan*/  atid; TYPE_6__ com; } ;
struct TYPE_9__ {int /*<<< orphan*/  tids; int /*<<< orphan*/ * ports; } ;
struct TYPE_10__ {TYPE_3__ lldi; } ;
struct TYPE_11__ {TYPE_4__ rdev; int /*<<< orphan*/  atids; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  DEAD ; 
 int /*<<< orphan*/  EHOSTUNREACH ; 
 int /*<<< orphan*/  FAKE_CPL_PUT_EP_SAFE ; 
 int /*<<< orphan*/  __state_set (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connect_reply_upcall (struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_clip_release (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  cxgb4_free_atid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  queue_arp_failure_cpl (struct c4iw_ep*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_erase_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void act_open_req_arp_failure(void *handle, struct sk_buff *skb)
{
	struct c4iw_ep *ep = handle;

	pr_err("ARP failure during connect\n");
	connect_reply_upcall(ep, -EHOSTUNREACH);
	__state_set(&ep->com, DEAD);
	if (ep->com.remote_addr.ss_family == AF_INET6) {
		struct sockaddr_in6 *sin6 =
			(struct sockaddr_in6 *)&ep->com.local_addr;
		cxgb4_clip_release(ep->com.dev->rdev.lldi.ports[0],
				   (const u32 *)&sin6->sin6_addr.s6_addr, 1);
	}
	xa_erase_irq(&ep->com.dev->atids, ep->atid);
	cxgb4_free_atid(ep->com.dev->rdev.lldi.tids, ep->atid);
	queue_arp_failure_cpl(ep, skb, FAKE_CPL_PUT_EP_SAFE);
}
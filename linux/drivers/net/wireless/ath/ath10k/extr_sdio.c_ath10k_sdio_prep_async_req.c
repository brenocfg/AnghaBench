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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct completion {int dummy; } ;
struct ath10k_sdio_bus_request {int eid; int htc_msg; int /*<<< orphan*/  list; struct completion* comp; int /*<<< orphan*/  address; struct sk_buff* skb; } ;
struct ath10k_sdio {int /*<<< orphan*/  wr_async_lock; int /*<<< orphan*/  wr_asyncq; } ;
struct ath10k {int dummy; } ;
typedef  enum ath10k_htc_ep_id { ____Placeholder_ath10k_htc_ep_id } ath10k_htc_ep_id ;

/* Variables and functions */
 int ENOMEM ; 
 struct ath10k_sdio_bus_request* ath10k_sdio_alloc_busreq (struct ath10k*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_sdio_prep_async_req(struct ath10k *ar, u32 addr,
				      struct sk_buff *skb,
				      struct completion *comp,
				      bool htc_msg, enum ath10k_htc_ep_id eid)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct ath10k_sdio_bus_request *bus_req;

	/* Allocate a bus request for the message and queue it on the
	 * SDIO workqueue.
	 */
	bus_req = ath10k_sdio_alloc_busreq(ar);
	if (!bus_req) {
		ath10k_warn(ar,
			    "unable to allocate bus request for async request\n");
		return -ENOMEM;
	}

	bus_req->skb = skb;
	bus_req->eid = eid;
	bus_req->address = addr;
	bus_req->htc_msg = htc_msg;
	bus_req->comp = comp;

	spin_lock_bh(&ar_sdio->wr_async_lock);
	list_add_tail(&bus_req->list, &ar_sdio->wr_asyncq);
	spin_unlock_bh(&ar_sdio->wr_async_lock);

	return 0;
}
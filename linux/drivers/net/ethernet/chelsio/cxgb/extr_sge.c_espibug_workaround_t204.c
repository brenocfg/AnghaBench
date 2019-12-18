#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct timer_list {int dummy; } ;
struct sk_buff {int* cb; int len; } ;
struct sge {scalar_t__ espibug_timeout; int /*<<< orphan*/  espibug_timer; struct sk_buff** espibug_skb; struct adapter* adapter; } ;
struct cpl_tx_pkt {int dummy; } ;
struct TYPE_3__ {unsigned int nports; } ;
struct adapter {int open_device_map; TYPE_2__* port; TYPE_1__ params; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int MAX_NPORTS ; 
 int PORT_MASK ; 
 int /*<<< orphan*/  ch_mac_addr ; 
 int /*<<< orphan*/  espibug_timer ; 
 struct sge* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 struct sge* sge ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_get (struct sk_buff*) ; 
 scalar_t__ t1_espi_get_mon_t204 (struct adapter*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_sge_tx (struct sk_buff*,struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void espibug_workaround_t204(struct timer_list *t)
{
	struct sge *sge = from_timer(sge, t, espibug_timer);
	struct adapter *adapter = sge->adapter;
	unsigned int nports = adapter->params.nports;
	u32 seop[MAX_NPORTS];

	if (adapter->open_device_map & PORT_MASK) {
		int i;

		if (t1_espi_get_mon_t204(adapter, &(seop[0]), 0) < 0)
			return;

		for (i = 0; i < nports; i++) {
			struct sk_buff *skb = sge->espibug_skb[i];

			if (!netif_running(adapter->port[i].dev) ||
			    netif_queue_stopped(adapter->port[i].dev) ||
			    !seop[i] || ((seop[i] & 0xfff) != 0) || !skb)
				continue;

			if (!skb->cb[0]) {
				skb_copy_to_linear_data_offset(skb,
						    sizeof(struct cpl_tx_pkt),
							       ch_mac_addr,
							       ETH_ALEN);
				skb_copy_to_linear_data_offset(skb,
							       skb->len - 10,
							       ch_mac_addr,
							       ETH_ALEN);
				skb->cb[0] = 0xff;
			}

			/* bump the reference count to avoid freeing of
			 * the skb once the DMA has completed.
			 */
			skb = skb_get(skb);
			t1_sge_tx(skb, adapter, 0, adapter->port[i].dev);
		}
	}
	mod_timer(&sge->espibug_timer, jiffies + sge->espibug_timeout);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct hfi1_vnic_vport_info {size_t num_rx_q; struct hfi1_vnic_rx_queue* rxq; int /*<<< orphan*/  vesw_id; int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; struct hfi1_devdata* dd; } ;
struct hfi1_vnic_rx_queue {int /*<<< orphan*/  skbq; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  vesws; } ;
struct hfi1_devdata {TYPE_1__ vnic; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_VNIC_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msix_vnic_synchronize_irq (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfi1_vnic_down(struct hfi1_vnic_vport_info *vinfo)
{
	struct hfi1_devdata *dd = vinfo->dd;
	u8 i;

	clear_bit(HFI1_VNIC_UP, &vinfo->flags);
	netif_carrier_off(vinfo->netdev);
	netif_tx_disable(vinfo->netdev);
	xa_erase(&dd->vnic.vesws, vinfo->vesw_id);

	/* ensure irqs see the change */
	msix_vnic_synchronize_irq(dd);

	/* remove unread skbs */
	for (i = 0; i < vinfo->num_rx_q; i++) {
		struct hfi1_vnic_rx_queue *rxq = &vinfo->rxq[i];

		napi_disable(&rxq->napi);
		skb_queue_purge(&rxq->skbq);
	}
}
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
typedef  int u64 ;
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/ * cb; int /*<<< orphan*/  data; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {void* expires; } ;
struct nes_hw_nic {int replenishing_rq; int rq_size; size_t rq_head; int qp_id; int /*<<< orphan*/  rq_lock; struct sk_buff** rx_skb; struct nes_hw_nic_rq_wqe* rq_vbase; } ;
struct nes_vnic {int max_frame_size; TYPE_1__ rq_wqes_timer; int /*<<< orphan*/  rx_skb_timer_running; int /*<<< orphan*/  rx_skbs_needed; struct nes_hw_nic nic; int /*<<< orphan*/  netdev; struct nes_device* nesdev; } ;
struct nes_rskb_cb {int maplen; scalar_t__ busaddr; } ;
struct nes_hw_nic_rq_wqe {void** wqe_words; } ;
struct nes_device {scalar_t__ regs; int /*<<< orphan*/  pcidev; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int HZ ; 
 size_t NES_NIC_RQ_WQE_FRAG0_HIGH_IDX ; 
 size_t NES_NIC_RQ_WQE_FRAG0_LOW_IDX ; 
 size_t NES_NIC_RQ_WQE_LENGTH_1_0_IDX ; 
 size_t NES_NIC_RQ_WQE_LENGTH_3_2_IDX ; 
 scalar_t__ NES_WQE_ALLOC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  barrier () ; 
 void* cpu_to_le32 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 void* jiffies ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nes_replenish_nic_rq(struct nes_vnic *nesvnic)
{
	unsigned long flags;
	dma_addr_t bus_address;
	struct sk_buff *skb;
	struct nes_hw_nic_rq_wqe *nic_rqe;
	struct nes_hw_nic *nesnic;
	struct nes_device *nesdev;
	struct nes_rskb_cb *cb;
	u32 rx_wqes_posted = 0;

	nesnic = &nesvnic->nic;
	nesdev = nesvnic->nesdev;
	spin_lock_irqsave(&nesnic->rq_lock, flags);
	if (nesnic->replenishing_rq !=0) {
		if (((nesnic->rq_size-1) == atomic_read(&nesvnic->rx_skbs_needed)) &&
				(atomic_read(&nesvnic->rx_skb_timer_running) == 0)) {
			atomic_set(&nesvnic->rx_skb_timer_running, 1);
			spin_unlock_irqrestore(&nesnic->rq_lock, flags);
			nesvnic->rq_wqes_timer.expires = jiffies + (HZ/2);	/* 1/2 second */
			add_timer(&nesvnic->rq_wqes_timer);
		} else
		spin_unlock_irqrestore(&nesnic->rq_lock, flags);
		return;
	}
	nesnic->replenishing_rq = 1;
	spin_unlock_irqrestore(&nesnic->rq_lock, flags);
	do {
		skb = dev_alloc_skb(nesvnic->max_frame_size);
		if (skb) {
			skb->dev = nesvnic->netdev;

			bus_address = pci_map_single(nesdev->pcidev,
					skb->data, nesvnic->max_frame_size, PCI_DMA_FROMDEVICE);
			cb = (struct nes_rskb_cb *)&skb->cb[0];
			cb->busaddr = bus_address;
			cb->maplen = nesvnic->max_frame_size;

			nic_rqe = &nesnic->rq_vbase[nesvnic->nic.rq_head];
			nic_rqe->wqe_words[NES_NIC_RQ_WQE_LENGTH_1_0_IDX] =
					cpu_to_le32(nesvnic->max_frame_size);
			nic_rqe->wqe_words[NES_NIC_RQ_WQE_LENGTH_3_2_IDX] = 0;
			nic_rqe->wqe_words[NES_NIC_RQ_WQE_FRAG0_LOW_IDX] =
					cpu_to_le32((u32)bus_address);
			nic_rqe->wqe_words[NES_NIC_RQ_WQE_FRAG0_HIGH_IDX] =
					cpu_to_le32((u32)((u64)bus_address >> 32));
			nesnic->rx_skb[nesnic->rq_head] = skb;
			nesnic->rq_head++;
			nesnic->rq_head &= nesnic->rq_size - 1;
			atomic_dec(&nesvnic->rx_skbs_needed);
			barrier();
			if (++rx_wqes_posted == 255) {
				nes_write32(nesdev->regs+NES_WQE_ALLOC, (rx_wqes_posted << 24) | nesnic->qp_id);
				rx_wqes_posted = 0;
			}
		} else {
			spin_lock_irqsave(&nesnic->rq_lock, flags);
			if (((nesnic->rq_size-1) == atomic_read(&nesvnic->rx_skbs_needed)) &&
					(atomic_read(&nesvnic->rx_skb_timer_running) == 0)) {
				atomic_set(&nesvnic->rx_skb_timer_running, 1);
				spin_unlock_irqrestore(&nesnic->rq_lock, flags);
				nesvnic->rq_wqes_timer.expires = jiffies + (HZ/2);	/* 1/2 second */
				add_timer(&nesvnic->rq_wqes_timer);
			} else
				spin_unlock_irqrestore(&nesnic->rq_lock, flags);
			break;
		}
	} while (atomic_read(&nesvnic->rx_skbs_needed));
	barrier();
	if (rx_wqes_posted)
		nes_write32(nesdev->regs+NES_WQE_ALLOC, (rx_wqes_posted << 24) | nesnic->qp_id);
	nesnic->replenishing_rq = 0;
}
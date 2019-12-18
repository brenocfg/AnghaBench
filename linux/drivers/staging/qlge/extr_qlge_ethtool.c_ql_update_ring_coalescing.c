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
struct rx_ring {int /*<<< orphan*/  cq_id; } ;
struct ql_adapter {size_t rss_ring_count; scalar_t__ tx_coalesce_usecs; scalar_t__ tx_max_coalesced_frames; int rx_ring_count; scalar_t__ rx_coalesce_usecs; scalar_t__ rx_max_coalesced_frames; int /*<<< orphan*/  ndev; struct rx_ring* rx_ring; } ;
struct cqicb {void* flags; void* pkt_delay; void* irq_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_LCQ ; 
 void* FLAGS_LI ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  ifup ; 
 scalar_t__ le16_to_cpu (void*) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int ql_write_cfg (struct ql_adapter*,struct cqicb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_update_ring_coalescing(struct ql_adapter *qdev)
{
	int i, status = 0;
	struct rx_ring *rx_ring;
	struct cqicb *cqicb;

	if (!netif_running(qdev->ndev))
		return status;

	/* Skip the default queue, and update the outbound handler
	 * queues if they changed.
	 */
	cqicb = (struct cqicb *)&qdev->rx_ring[qdev->rss_ring_count];
	if (le16_to_cpu(cqicb->irq_delay) != qdev->tx_coalesce_usecs ||
		le16_to_cpu(cqicb->pkt_delay) !=
				qdev->tx_max_coalesced_frames) {
		for (i = qdev->rss_ring_count; i < qdev->rx_ring_count; i++) {
			rx_ring = &qdev->rx_ring[i];
			cqicb = (struct cqicb *)rx_ring;
			cqicb->irq_delay = cpu_to_le16(qdev->tx_coalesce_usecs);
			cqicb->pkt_delay =
			    cpu_to_le16(qdev->tx_max_coalesced_frames);
			cqicb->flags = FLAGS_LI;
			status = ql_write_cfg(qdev, cqicb, sizeof(*cqicb),
						CFG_LCQ, rx_ring->cq_id);
			if (status) {
				netif_err(qdev, ifup, qdev->ndev,
					  "Failed to load CQICB.\n");
				goto exit;
			}
		}
	}

	/* Update the inbound (RSS) handler queues if they changed. */
	cqicb = (struct cqicb *)&qdev->rx_ring[0];
	if (le16_to_cpu(cqicb->irq_delay) != qdev->rx_coalesce_usecs ||
		le16_to_cpu(cqicb->pkt_delay) !=
					qdev->rx_max_coalesced_frames) {
		for (i = 0; i < qdev->rss_ring_count; i++, rx_ring++) {
			rx_ring = &qdev->rx_ring[i];
			cqicb = (struct cqicb *)rx_ring;
			cqicb->irq_delay = cpu_to_le16(qdev->rx_coalesce_usecs);
			cqicb->pkt_delay =
			    cpu_to_le16(qdev->rx_max_coalesced_frames);
			cqicb->flags = FLAGS_LI;
			status = ql_write_cfg(qdev, cqicb, sizeof(*cqicb),
						CFG_LCQ, rx_ring->cq_id);
			if (status) {
				netif_err(qdev, ifup, qdev->ndev,
					  "Failed to load CQICB.\n");
				goto exit;
			}
		}
	}
exit:
	return status;
}
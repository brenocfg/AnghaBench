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
struct tx_sw_desc {int /*<<< orphan*/ * skb; scalar_t__ eop; } ;
struct sge_txq {unsigned int cidx; scalar_t__ cntxt_id; unsigned int size; struct tx_sw_desc* sdesc; } ;
struct pci_dev {int dummy; } ;
struct adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 scalar_t__ FW_TUNNEL_SGEEC_START ; 
 int /*<<< orphan*/  dev_consume_skb_any (int /*<<< orphan*/ *) ; 
 scalar_t__ need_skb_unmap () ; 
 int /*<<< orphan*/  unmap_skb (int /*<<< orphan*/ *,struct sge_txq*,unsigned int,struct pci_dev*) ; 

__attribute__((used)) static void free_tx_desc(struct adapter *adapter, struct sge_txq *q,
			 unsigned int n)
{
	struct tx_sw_desc *d;
	struct pci_dev *pdev = adapter->pdev;
	unsigned int cidx = q->cidx;

	const int need_unmap = need_skb_unmap() &&
			       q->cntxt_id >= FW_TUNNEL_SGEEC_START;

	d = &q->sdesc[cidx];
	while (n--) {
		if (d->skb) {	/* an SGL is present */
			if (need_unmap)
				unmap_skb(d->skb, q, cidx, pdev);
			if (d->eop) {
				dev_consume_skb_any(d->skb);
				d->skb = NULL;
			}
		}
		++d;
		if (++cidx == q->size) {
			cidx = 0;
			d = q->sdesc;
		}
	}
	q->cidx = cidx;
}
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
struct tx_sw_desc {int /*<<< orphan*/ * skb; int /*<<< orphan*/  sgl; } ;
struct sge_txq {unsigned int cidx; unsigned int size; struct tx_sw_desc* sdesc; } ;
struct device {int dummy; } ;
struct adapter {struct device* pdev_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_consume_skb_any (int /*<<< orphan*/ *) ; 
 scalar_t__ need_skb_unmap () ; 
 int /*<<< orphan*/  unmap_sgl (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sge_txq*) ; 

__attribute__((used)) static void free_tx_desc(struct adapter *adapter, struct sge_txq *tq,
			 unsigned int n, bool unmap)
{
	struct tx_sw_desc *sdesc;
	unsigned int cidx = tq->cidx;
	struct device *dev = adapter->pdev_dev;

	const int need_unmap = need_skb_unmap() && unmap;

	sdesc = &tq->sdesc[cidx];
	while (n--) {
		/*
		 * If we kept a reference to the original TX skb, we need to
		 * unmap it from PCI DMA space (if required) and free it.
		 */
		if (sdesc->skb) {
			if (need_unmap)
				unmap_sgl(dev, sdesc->skb, sdesc->sgl, tq);
			dev_consume_skb_any(sdesc->skb);
			sdesc->skb = NULL;
		}

		sdesc++;
		if (++cidx == tq->size) {
			cidx = 0;
			sdesc = tq->sdesc;
		}
	}
	tq->cidx = cidx;
}
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
 int /*<<< orphan*/  unmap_sgl (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sge_txq*) ; 

void free_tx_desc(struct adapter *adap, struct sge_txq *q,
		  unsigned int n, bool unmap)
{
	struct tx_sw_desc *d;
	unsigned int cidx = q->cidx;
	struct device *dev = adap->pdev_dev;

	d = &q->sdesc[cidx];
	while (n--) {
		if (d->skb) {                       /* an SGL is present */
			if (unmap)
				unmap_sgl(dev, d->skb, d->sgl, q);
			dev_consume_skb_any(d->skb);
			d->skb = NULL;
		}
		++d;
		if (++cidx == q->size) {
			cidx = 0;
			d = q->sdesc;
		}
	}
	q->cidx = cidx;
}
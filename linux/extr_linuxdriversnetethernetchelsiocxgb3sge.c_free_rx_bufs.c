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
struct TYPE_2__ {int /*<<< orphan*/ * page; } ;
struct sge_fl {unsigned int cidx; unsigned int size; TYPE_1__ pg_chunk; int /*<<< orphan*/  order; struct rx_sw_desc* sdesc; int /*<<< orphan*/  credits; } ;
struct rx_sw_desc {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_rx_desc (struct pci_dev*,struct sge_fl*,struct rx_sw_desc*) ; 

__attribute__((used)) static void free_rx_bufs(struct pci_dev *pdev, struct sge_fl *q)
{
	unsigned int cidx = q->cidx;

	while (q->credits--) {
		struct rx_sw_desc *d = &q->sdesc[cidx];


		clear_rx_desc(pdev, q, d);
		if (++cidx == q->size)
			cidx = 0;
	}

	if (q->pg_chunk.page) {
		__free_pages(q->pg_chunk.page, q->order);
		q->pg_chunk.page = NULL;
	}
}
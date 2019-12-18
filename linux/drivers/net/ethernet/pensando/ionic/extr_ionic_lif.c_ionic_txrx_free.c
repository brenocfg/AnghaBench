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
struct ionic_lif {unsigned int nxqs; TYPE_2__* rxqcqs; TYPE_1__* txqcqs; } ;
struct TYPE_4__ {int /*<<< orphan*/ * qcq; } ;
struct TYPE_3__ {int /*<<< orphan*/ * qcq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ionic_qcq_free (struct ionic_lif*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ionic_txrx_free(struct ionic_lif *lif)
{
	unsigned int i;

	for (i = 0; i < lif->nxqs; i++) {
		ionic_qcq_free(lif, lif->txqcqs[i].qcq);
		lif->txqcqs[i].qcq = NULL;

		ionic_qcq_free(lif, lif->rxqcqs[i].qcq);
		lif->rxqcqs[i].qcq = NULL;
	}
}
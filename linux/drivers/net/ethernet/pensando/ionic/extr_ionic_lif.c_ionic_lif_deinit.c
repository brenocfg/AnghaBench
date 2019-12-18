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
struct ionic_lif {TYPE_1__* adminqcq; TYPE_1__* notifyqcq; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_LIF_INITED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_lif_qcq_deinit (struct ionic_lif*,TYPE_1__*) ; 
 int /*<<< orphan*/  ionic_lif_reset (struct ionic_lif*) ; 
 int /*<<< orphan*/  ionic_lif_rss_deinit (struct ionic_lif*) ; 
 int /*<<< orphan*/  ionic_rx_filters_deinit (struct ionic_lif*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ionic_lif_deinit(struct ionic_lif *lif)
{
	if (!test_bit(IONIC_LIF_INITED, lif->state))
		return;

	clear_bit(IONIC_LIF_INITED, lif->state);

	ionic_rx_filters_deinit(lif);
	ionic_lif_rss_deinit(lif);

	napi_disable(&lif->adminqcq->napi);
	ionic_lif_qcq_deinit(lif, lif->notifyqcq);
	ionic_lif_qcq_deinit(lif, lif->adminqcq);

	ionic_lif_reset(lif);
}
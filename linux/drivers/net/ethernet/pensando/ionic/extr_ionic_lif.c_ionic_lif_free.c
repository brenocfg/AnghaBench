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
struct ionic_lif {int /*<<< orphan*/  netdev; int /*<<< orphan*/  list; int /*<<< orphan*/ * dbid_inuse; int /*<<< orphan*/ * kern_dbpage; TYPE_1__* ionic; scalar_t__ info_pa; int /*<<< orphan*/ * info; int /*<<< orphan*/  info_sz; scalar_t__ rss_ind_tbl_pa; int /*<<< orphan*/ * rss_ind_tbl; int /*<<< orphan*/  rss_ind_tbl_sz; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_bus_unmap_dbpage (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ionic_debugfs_del_lif (struct ionic_lif*) ; 
 int /*<<< orphan*/  ionic_lif_reset (struct ionic_lif*) ; 
 int /*<<< orphan*/  ionic_qcqs_free (struct ionic_lif*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ionic_lif_free(struct ionic_lif *lif)
{
	struct device *dev = lif->ionic->dev;

	/* free rss indirection table */
	dma_free_coherent(dev, lif->rss_ind_tbl_sz, lif->rss_ind_tbl,
			  lif->rss_ind_tbl_pa);
	lif->rss_ind_tbl = NULL;
	lif->rss_ind_tbl_pa = 0;

	/* free queues */
	ionic_qcqs_free(lif);
	ionic_lif_reset(lif);

	/* free lif info */
	dma_free_coherent(dev, lif->info_sz, lif->info, lif->info_pa);
	lif->info = NULL;
	lif->info_pa = 0;

	/* unmap doorbell page */
	ionic_bus_unmap_dbpage(lif->ionic, lif->kern_dbpage);
	lif->kern_dbpage = NULL;
	kfree(lif->dbid_inuse);
	lif->dbid_inuse = NULL;

	/* free netdev & lif */
	ionic_debugfs_del_lif(lif);
	list_del(&lif->list);
	free_netdev(lif->netdev);
}
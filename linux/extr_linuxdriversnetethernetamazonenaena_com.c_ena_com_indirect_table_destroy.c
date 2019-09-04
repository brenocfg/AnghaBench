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
struct ena_rss {unsigned long long tbl_log_size; int /*<<< orphan*/ * host_rss_ind_tbl; int /*<<< orphan*/ * rss_ind_tbl; int /*<<< orphan*/  rss_ind_tbl_dma_addr; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; struct ena_rss rss; } ;
struct ena_admin_rss_ind_table_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_com_indirect_table_destroy(struct ena_com_dev *ena_dev)
{
	struct ena_rss *rss = &ena_dev->rss;
	size_t tbl_size = (1ULL << rss->tbl_log_size) *
		sizeof(struct ena_admin_rss_ind_table_entry);

	if (rss->rss_ind_tbl)
		dma_free_coherent(ena_dev->dmadev, tbl_size, rss->rss_ind_tbl,
				  rss->rss_ind_tbl_dma_addr);
	rss->rss_ind_tbl = NULL;

	if (rss->host_rss_ind_tbl)
		devm_kfree(ena_dev->dmadev, rss->host_rss_ind_tbl);
	rss->host_rss_ind_tbl = NULL;
}
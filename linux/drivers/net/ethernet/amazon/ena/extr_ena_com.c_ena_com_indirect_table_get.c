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
typedef  unsigned long long u32 ;
struct ena_rss {unsigned long long tbl_log_size; unsigned long long* host_rss_ind_tbl; int /*<<< orphan*/  rss_ind_tbl_dma_addr; } ;
struct ena_com_dev {struct ena_rss rss; } ;
struct ena_admin_rss_ind_table_entry {int dummy; } ;
struct ena_admin_get_feat_resp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_RSS_REDIRECTION_TABLE_CONFIG ; 
 int ena_com_get_feature_ex (struct ena_com_dev*,struct ena_admin_get_feat_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ) ; 
 int ena_com_ind_tbl_convert_from_device (struct ena_com_dev*) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_indirect_table_get(struct ena_com_dev *ena_dev, u32 *ind_tbl)
{
	struct ena_rss *rss = &ena_dev->rss;
	struct ena_admin_get_feat_resp get_resp;
	u32 tbl_size;
	int i, rc;

	tbl_size = (1ULL << rss->tbl_log_size) *
		sizeof(struct ena_admin_rss_ind_table_entry);

	rc = ena_com_get_feature_ex(ena_dev, &get_resp,
				    ENA_ADMIN_RSS_REDIRECTION_TABLE_CONFIG,
				    rss->rss_ind_tbl_dma_addr,
				    tbl_size, 0);
	if (unlikely(rc))
		return rc;

	if (!ind_tbl)
		return 0;

	rc = ena_com_ind_tbl_convert_from_device(ena_dev);
	if (unlikely(rc))
		return rc;

	for (i = 0; i < (1 << rss->tbl_log_size); i++)
		ind_tbl[i] = rss->host_rss_ind_tbl[i];

	return 0;
}
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
struct ena_llq_configurations {int dummy; } ;
struct ena_eth_io_tx_desc {int dummy; } ;
struct ena_com_llq_info {scalar_t__ desc_list_entry_size; int descs_num_before_header; } ;
struct ena_com_dev {scalar_t__ tx_max_header_size; int /*<<< orphan*/  tx_mem_queue_type; struct ena_com_llq_info llq_info; } ;
struct ena_admin_feature_llq_desc {int /*<<< orphan*/  max_llq_num; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENA_ADMIN_PLACEMENT_POLICY_DEV ; 
 int /*<<< orphan*/  ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 int ena_com_config_llq_info (struct ena_com_dev*,struct ena_admin_feature_llq_desc*,struct ena_llq_configurations*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_config_dev_mode(struct ena_com_dev *ena_dev,
			    struct ena_admin_feature_llq_desc *llq_features,
			    struct ena_llq_configurations *llq_default_cfg)
{
	struct ena_com_llq_info *llq_info = &ena_dev->llq_info;
	int rc;

	if (!llq_features->max_llq_num) {
		ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_HOST;
		return 0;
	}

	rc = ena_com_config_llq_info(ena_dev, llq_features, llq_default_cfg);
	if (rc)
		return rc;

	ena_dev->tx_max_header_size = llq_info->desc_list_entry_size -
		(llq_info->descs_num_before_header * sizeof(struct ena_eth_io_tx_desc));

	if (unlikely(ena_dev->tx_max_header_size == 0)) {
		pr_err("the size of the LLQ entry is smaller than needed\n");
		return -EINVAL;
	}

	ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_DEV;

	return 0;
}
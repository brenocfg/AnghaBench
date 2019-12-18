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
typedef  int u16 ;
struct ena_llq_configurations {int llq_header_location; int llq_stride_ctrl; int llq_ring_entry_size; int llq_ring_entry_size_value; int llq_num_decs_before_header; } ;
struct ena_eth_io_tx_desc {int dummy; } ;
struct ena_com_llq_info {scalar_t__ header_location_ctrl; int desc_stride_ctrl; int desc_list_entry_size_ctrl; int desc_list_entry_size; int descs_per_entry; int descs_num_before_header; int max_entries_in_tx_burst; } ;
struct ena_com_dev {struct ena_com_llq_info llq_info; } ;
struct ena_admin_feature_llq_desc {int header_location_ctrl_supported; int descriptors_stride_ctrl_supported; int entry_size_ctrl_supported; int desc_num_before_header_supported; int max_tx_burst_size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ENA_ADMIN_INLINE_HEADER ; 
 int ENA_ADMIN_LIST_ENTRY_SIZE_128B ; 
 int ENA_ADMIN_LIST_ENTRY_SIZE_192B ; 
 int ENA_ADMIN_LIST_ENTRY_SIZE_256B ; 
 int ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_1 ; 
 int ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_2 ; 
 int ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_4 ; 
 int ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_8 ; 
 int ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY ; 
 int ENA_ADMIN_SINGLE_DESC_PER_ENTRY ; 
 int ena_com_set_llq (struct ena_com_dev*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct ena_com_llq_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ena_com_config_llq_info(struct ena_com_dev *ena_dev,
				   struct ena_admin_feature_llq_desc *llq_features,
				   struct ena_llq_configurations *llq_default_cfg)
{
	struct ena_com_llq_info *llq_info = &ena_dev->llq_info;
	u16 supported_feat;
	int rc;

	memset(llq_info, 0, sizeof(*llq_info));

	supported_feat = llq_features->header_location_ctrl_supported;

	if (likely(supported_feat & llq_default_cfg->llq_header_location)) {
		llq_info->header_location_ctrl =
			llq_default_cfg->llq_header_location;
	} else {
		pr_err("Invalid header location control, supported: 0x%x\n",
		       supported_feat);
		return -EINVAL;
	}

	if (likely(llq_info->header_location_ctrl == ENA_ADMIN_INLINE_HEADER)) {
		supported_feat = llq_features->descriptors_stride_ctrl_supported;
		if (likely(supported_feat & llq_default_cfg->llq_stride_ctrl)) {
			llq_info->desc_stride_ctrl = llq_default_cfg->llq_stride_ctrl;
		} else	{
			if (supported_feat & ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY) {
				llq_info->desc_stride_ctrl = ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY;
			} else if (supported_feat & ENA_ADMIN_SINGLE_DESC_PER_ENTRY) {
				llq_info->desc_stride_ctrl = ENA_ADMIN_SINGLE_DESC_PER_ENTRY;
			} else {
				pr_err("Invalid desc_stride_ctrl, supported: 0x%x\n",
				       supported_feat);
				return -EINVAL;
			}

			pr_err("Default llq stride ctrl is not supported, performing fallback, default: 0x%x, supported: 0x%x, used: 0x%x\n",
			       llq_default_cfg->llq_stride_ctrl, supported_feat,
			       llq_info->desc_stride_ctrl);
		}
	} else {
		llq_info->desc_stride_ctrl = 0;
	}

	supported_feat = llq_features->entry_size_ctrl_supported;
	if (likely(supported_feat & llq_default_cfg->llq_ring_entry_size)) {
		llq_info->desc_list_entry_size_ctrl = llq_default_cfg->llq_ring_entry_size;
		llq_info->desc_list_entry_size = llq_default_cfg->llq_ring_entry_size_value;
	} else {
		if (supported_feat & ENA_ADMIN_LIST_ENTRY_SIZE_128B) {
			llq_info->desc_list_entry_size_ctrl = ENA_ADMIN_LIST_ENTRY_SIZE_128B;
			llq_info->desc_list_entry_size = 128;
		} else if (supported_feat & ENA_ADMIN_LIST_ENTRY_SIZE_192B) {
			llq_info->desc_list_entry_size_ctrl = ENA_ADMIN_LIST_ENTRY_SIZE_192B;
			llq_info->desc_list_entry_size = 192;
		} else if (supported_feat & ENA_ADMIN_LIST_ENTRY_SIZE_256B) {
			llq_info->desc_list_entry_size_ctrl = ENA_ADMIN_LIST_ENTRY_SIZE_256B;
			llq_info->desc_list_entry_size = 256;
		} else {
			pr_err("Invalid entry_size_ctrl, supported: 0x%x\n",
			       supported_feat);
			return -EINVAL;
		}

		pr_err("Default llq ring entry size is not supported, performing fallback, default: 0x%x, supported: 0x%x, used: 0x%x\n",
		       llq_default_cfg->llq_ring_entry_size, supported_feat,
		       llq_info->desc_list_entry_size);
	}
	if (unlikely(llq_info->desc_list_entry_size & 0x7)) {
		/* The desc list entry size should be whole multiply of 8
		 * This requirement comes from __iowrite64_copy()
		 */
		pr_err("illegal entry size %d\n",
		       llq_info->desc_list_entry_size);
		return -EINVAL;
	}

	if (llq_info->desc_stride_ctrl == ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY)
		llq_info->descs_per_entry = llq_info->desc_list_entry_size /
			sizeof(struct ena_eth_io_tx_desc);
	else
		llq_info->descs_per_entry = 1;

	supported_feat = llq_features->desc_num_before_header_supported;
	if (likely(supported_feat & llq_default_cfg->llq_num_decs_before_header)) {
		llq_info->descs_num_before_header = llq_default_cfg->llq_num_decs_before_header;
	} else {
		if (supported_feat & ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_2) {
			llq_info->descs_num_before_header = ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_2;
		} else if (supported_feat & ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_1) {
			llq_info->descs_num_before_header = ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_1;
		} else if (supported_feat & ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_4) {
			llq_info->descs_num_before_header = ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_4;
		} else if (supported_feat & ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_8) {
			llq_info->descs_num_before_header = ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_8;
		} else {
			pr_err("Invalid descs_num_before_header, supported: 0x%x\n",
			       supported_feat);
			return -EINVAL;
		}

		pr_err("Default llq num descs before header is not supported, performing fallback, default: 0x%x, supported: 0x%x, used: 0x%x\n",
		       llq_default_cfg->llq_num_decs_before_header,
		       supported_feat, llq_info->descs_num_before_header);
	}

	llq_info->max_entries_in_tx_burst =
		(u16)(llq_features->max_tx_burst_size /	llq_default_cfg->llq_ring_entry_size_value);

	rc = ena_com_set_llq(ena_dev);
	if (rc)
		pr_err("Cannot set LLQ configuration: %d\n", rc);

	return rc;
}
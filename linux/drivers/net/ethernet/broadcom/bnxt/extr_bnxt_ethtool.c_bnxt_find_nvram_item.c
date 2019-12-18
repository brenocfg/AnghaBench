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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct hwrm_nvm_find_dir_entry_output {int /*<<< orphan*/  dir_data_length; int /*<<< orphan*/  dir_item_length; int /*<<< orphan*/  dir_idx; } ;
struct hwrm_nvm_find_dir_entry_input {int /*<<< orphan*/  opt_ordinal; void* dir_ext; void* dir_ordinal; void* dir_type; scalar_t__ dir_idx; scalar_t__ enables; int /*<<< orphan*/  member_0; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; struct hwrm_nvm_find_dir_entry_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_NVM_FIND_DIR_ENTRY ; 
 int /*<<< orphan*/  NVM_FIND_DIR_ENTRY_REQ_OPT_ORDINAL_EQ ; 
 int _hwrm_send_message_silent (struct bnxt*,struct hwrm_nvm_find_dir_entry_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_nvm_find_dir_entry_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_find_nvram_item(struct net_device *dev, u16 type, u16 ordinal,
				u16 ext, u16 *index, u32 *item_length,
				u32 *data_length)
{
	struct bnxt *bp = netdev_priv(dev);
	int rc;
	struct hwrm_nvm_find_dir_entry_input req = {0};
	struct hwrm_nvm_find_dir_entry_output *output = bp->hwrm_cmd_resp_addr;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_FIND_DIR_ENTRY, -1, -1);
	req.enables = 0;
	req.dir_idx = 0;
	req.dir_type = cpu_to_le16(type);
	req.dir_ordinal = cpu_to_le16(ordinal);
	req.dir_ext = cpu_to_le16(ext);
	req.opt_ordinal = NVM_FIND_DIR_ENTRY_REQ_OPT_ORDINAL_EQ;
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message_silent(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc == 0) {
		if (index)
			*index = le16_to_cpu(output->dir_idx);
		if (item_length)
			*item_length = le32_to_cpu(output->dir_item_length);
		if (data_length)
			*data_length = le32_to_cpu(output->dir_data_length);
	}
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}
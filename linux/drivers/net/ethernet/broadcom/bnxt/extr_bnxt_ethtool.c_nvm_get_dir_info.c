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
struct net_device {int dummy; } ;
struct hwrm_nvm_get_dir_info_output {int /*<<< orphan*/  entry_length; int /*<<< orphan*/  entries; } ;
struct hwrm_nvm_get_dir_info_input {int /*<<< orphan*/  member_0; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; struct hwrm_nvm_get_dir_info_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_NVM_GET_DIR_INFO ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_nvm_get_dir_info_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_nvm_get_dir_info_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nvm_get_dir_info(struct net_device *dev, u32 *entries, u32 *length)
{
	struct bnxt *bp = netdev_priv(dev);
	int rc;
	struct hwrm_nvm_get_dir_info_input req = {0};
	struct hwrm_nvm_get_dir_info_output *output = bp->hwrm_cmd_resp_addr;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_GET_DIR_INFO, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (!rc) {
		*entries = le32_to_cpu(output->entries);
		*length = le32_to_cpu(output->entry_length);
	}
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}
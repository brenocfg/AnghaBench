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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct hwrm_nvm_erase_dir_entry_input {int /*<<< orphan*/  dir_idx; int /*<<< orphan*/  member_0; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_NVM_ERASE_DIR_ENTRY ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_nvm_erase_dir_entry_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_nvm_erase_dir_entry_input*,int,int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_erase_nvram_directory(struct net_device *dev, u8 index)
{
	struct bnxt *bp = netdev_priv(dev);
	struct hwrm_nvm_erase_dir_entry_input req = {0};

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_ERASE_DIR_ENTRY, -1, -1);
	req.dir_idx = cpu_to_le16(index);
	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}
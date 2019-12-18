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
struct iwl_trans_pcie {int ucode_write_complete; int /*<<< orphan*/  ucode_write_waitq; } ;
struct iwl_trans {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_load_firmware_chunk_fh (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_grab_nic_access (struct iwl_trans*,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_pcie_dump_regs (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (struct iwl_trans*,unsigned long*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int iwl_pcie_load_firmware_chunk(struct iwl_trans *trans,
					u32 dst_addr, dma_addr_t phy_addr,
					u32 byte_cnt)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	unsigned long flags;
	int ret;

	trans_pcie->ucode_write_complete = false;

	if (!iwl_trans_grab_nic_access(trans, &flags))
		return -EIO;

	iwl_pcie_load_firmware_chunk_fh(trans, dst_addr, phy_addr,
					byte_cnt);
	iwl_trans_release_nic_access(trans, &flags);

	ret = wait_event_timeout(trans_pcie->ucode_write_waitq,
				 trans_pcie->ucode_write_complete, 5 * HZ);
	if (!ret) {
		IWL_ERR(trans, "Failed to load firmware chunk!\n");
		iwl_trans_pcie_dump_regs(trans);
		return -ETIMEDOUT;
	}

	return 0;
}
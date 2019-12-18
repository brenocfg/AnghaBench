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
struct iwl_trans_pcie {int max_tbs; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ iwl_pcie_tfd_tb_get_len (struct iwl_trans*,void*,int) ; 

__attribute__((used)) static u32 iwl_trans_pcie_get_cmdlen(struct iwl_trans *trans, void *tfd)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 cmdlen = 0;
	int i;

	for (i = 0; i < trans_pcie->max_tbs; i++)
		cmdlen += iwl_pcie_tfd_tb_get_len(trans, tfd, i);

	return cmdlen;
}
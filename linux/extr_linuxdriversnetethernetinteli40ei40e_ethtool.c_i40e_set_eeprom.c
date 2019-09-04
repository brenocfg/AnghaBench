#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {int vendor_id; int device_id; int debug_mask; TYPE_3__ aq; } ;
struct i40e_pf {TYPE_2__* pdev; int /*<<< orphan*/  state; struct i40e_hw hw; } ;
struct i40e_nvm_access {int config; int /*<<< orphan*/  data_size; int /*<<< orphan*/  offset; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct ethtool_eeprom {int magic; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int I40E_DEBUG_NVM ; 
 int I40E_NVM_MOD_PNT_MASK ; 
 int /*<<< orphan*/  __I40E_RESET_INTR_RECEIVED ; 
 int /*<<< orphan*/  __I40E_RESET_RECOVERY_PENDING ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40e_nvmupd_command (struct i40e_hw*,struct i40e_nvm_access*,int /*<<< orphan*/ *,int*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_set_eeprom(struct net_device *netdev,
			   struct ethtool_eeprom *eeprom, u8 *bytes)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_hw *hw = &np->vsi->back->hw;
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_nvm_access *cmd = (struct i40e_nvm_access *)eeprom;
	int ret_val = 0;
	int errno = 0;
	u32 magic;

	/* normal ethtool set_eeprom is not supported */
	magic = hw->vendor_id | (hw->device_id << 16);
	if (eeprom->magic == magic)
		errno = -EOPNOTSUPP;
	/* check for NVMUpdate access method */
	else if (!eeprom->magic || (eeprom->magic >> 16) != hw->device_id)
		errno = -EINVAL;
	else if (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state) ||
		 test_bit(__I40E_RESET_INTR_RECEIVED, pf->state))
		errno = -EBUSY;
	else
		ret_val = i40e_nvmupd_command(hw, cmd, bytes, &errno);

	if ((errno || ret_val) && (hw->debug_mask & I40E_DEBUG_NVM))
		dev_info(&pf->pdev->dev,
			 "NVMUpdate write failed err=%d status=0x%x errno=%d module=%d offset=0x%x size=%d\n",
			 ret_val, hw->aq.asq_last_status, errno,
			 (u8)(cmd->config & I40E_NVM_MOD_PNT_MASK),
			 cmd->offset, cmd->data_size);

	return errno;
}
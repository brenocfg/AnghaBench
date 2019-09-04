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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int magic; int offset; int /*<<< orphan*/  len; } ;
struct atl1e_hw {int vendor_id; int device_id; } ;
struct atl1e_adapter {struct atl1e_hw hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ atl1e_check_eeprom_exist (struct atl1e_hw*) ; 
 int /*<<< orphan*/  atl1e_read_eeprom (struct atl1e_hw*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atl1e_get_eeprom(struct net_device *netdev,
		struct ethtool_eeprom *eeprom, u8 *bytes)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);
	struct atl1e_hw *hw = &adapter->hw;
	u32 *eeprom_buff;
	int first_dword, last_dword;
	int ret_val = 0;
	int i;

	if (eeprom->len == 0)
		return -EINVAL;

	if (atl1e_check_eeprom_exist(hw)) /* not exist */
		return -EINVAL;

	eeprom->magic = hw->vendor_id | (hw->device_id << 16);

	first_dword = eeprom->offset >> 2;
	last_dword = (eeprom->offset + eeprom->len - 1) >> 2;

	eeprom_buff = kmalloc_array(last_dword - first_dword + 1, sizeof(u32),
				    GFP_KERNEL);
	if (eeprom_buff == NULL)
		return -ENOMEM;

	for (i = first_dword; i < last_dword; i++) {
		if (!atl1e_read_eeprom(hw, i * 4, &(eeprom_buff[i-first_dword]))) {
			kfree(eeprom_buff);
			return -EIO;
		}
	}

	memcpy(bytes, (u8 *)eeprom_buff + (eeprom->offset & 3),
			eeprom->len);
	kfree(eeprom_buff);

	return ret_val;
}
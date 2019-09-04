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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {struct e1000_hw hw; } ;
struct ethtool_eeprom {int offset; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be16_to_cpus (int*) ; 
 scalar_t__ igb_read_phy_reg_i2c (struct e1000_hw*,int,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_get_module_eeprom(struct net_device *netdev,
				 struct ethtool_eeprom *ee, u8 *data)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 status = 0;
	u16 *dataword;
	u16 first_word, last_word;
	int i = 0;

	if (ee->len == 0)
		return -EINVAL;

	first_word = ee->offset >> 1;
	last_word = (ee->offset + ee->len - 1) >> 1;

	dataword = kmalloc_array(last_word - first_word + 1, sizeof(u16),
				 GFP_KERNEL);
	if (!dataword)
		return -ENOMEM;

	/* Read EEPROM block, SFF-8079/SFF-8472, word at a time */
	for (i = 0; i < last_word - first_word + 1; i++) {
		status = igb_read_phy_reg_i2c(hw, (first_word + i) * 2,
					      &dataword[i]);
		if (status) {
			/* Error occurred while reading module */
			kfree(dataword);
			return -EIO;
		}

		be16_to_cpus(&dataword[i]);
	}

	memcpy(data, (u8 *)dataword + (ee->offset & 1), ee->len);
	kfree(dataword);

	return 0;
}
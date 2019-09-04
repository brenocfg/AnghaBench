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
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_3__ dev; } ;
struct ethtool_eeprom {int magic; int offset; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_2__ nvm; } ;
struct e1000_adapter {TYPE_1__* pdev; struct e1000_hw hw; } ;
struct TYPE_4__ {int vendor; int device; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ e1000_nvm_eeprom_spi ; 
 int e1000_read_nvm (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpus (int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e1000_get_eeprom(struct net_device *netdev,
			    struct ethtool_eeprom *eeprom, u8 *bytes)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	int first_word;
	int last_word;
	int ret_val = 0;
	u16 i;

	if (eeprom->len == 0)
		return -EINVAL;

	eeprom->magic = adapter->pdev->vendor | (adapter->pdev->device << 16);

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;

	eeprom_buff = kmalloc_array(last_word - first_word + 1, sizeof(u16),
				    GFP_KERNEL);
	if (!eeprom_buff)
		return -ENOMEM;

	pm_runtime_get_sync(netdev->dev.parent);

	if (hw->nvm.type == e1000_nvm_eeprom_spi) {
		ret_val = e1000_read_nvm(hw, first_word,
					 last_word - first_word + 1,
					 eeprom_buff);
	} else {
		for (i = 0; i < last_word - first_word + 1; i++) {
			ret_val = e1000_read_nvm(hw, first_word + i, 1,
						 &eeprom_buff[i]);
			if (ret_val)
				break;
		}
	}

	pm_runtime_put_sync(netdev->dev.parent);

	if (ret_val) {
		/* a read error occurred, throw away the result */
		memset(eeprom_buff, 0xff, sizeof(u16) *
		       (last_word - first_word + 1));
	} else {
		/* Device's eeprom is always little-endian, word addressable */
		for (i = 0; i < last_word - first_word + 1; i++)
			le16_to_cpus(&eeprom_buff[i]);
	}

	memcpy(bytes, (u8 *)eeprom_buff + (eeprom->offset & 1), eeprom->len);
	kfree(eeprom_buff);

	return ret_val;
}
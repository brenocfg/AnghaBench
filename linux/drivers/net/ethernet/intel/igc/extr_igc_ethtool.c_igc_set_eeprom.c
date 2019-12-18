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
struct net_device {int dummy; } ;
struct TYPE_5__ {int (* read ) (struct igc_hw*,int,int,int*) ;int (* write ) (struct igc_hw*,int,int,int*) ;int /*<<< orphan*/  (* update ) (struct igc_hw*) ;} ;
struct TYPE_6__ {int word_size; TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct igc_hw {int vendor_id; int device_id; TYPE_3__ nvm; TYPE_1__ mac; } ;
struct igc_adapter {struct igc_hw hw; } ;
struct ethtool_eeprom {int magic; int offset; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cpu_to_le16 (int) ; 
 int /*<<< orphan*/  igc_get_flash_presence_i225 (struct igc_hw*) ; 
 scalar_t__ igc_i225 ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpus (int*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct igc_adapter* netdev_priv (struct net_device*) ; 
 int stub1 (struct igc_hw*,int,int,int*) ; 
 int stub2 (struct igc_hw*,int,int,int*) ; 
 int stub3 (struct igc_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub4 (struct igc_hw*) ; 

__attribute__((used)) static int igc_set_eeprom(struct net_device *netdev,
			  struct ethtool_eeprom *eeprom, u8 *bytes)
{
	struct igc_adapter *adapter = netdev_priv(netdev);
	struct igc_hw *hw = &adapter->hw;
	int max_len, first_word, last_word, ret_val = 0;
	u16 *eeprom_buff;
	void *ptr;
	u16 i;

	if (eeprom->len == 0)
		return -EOPNOTSUPP;

	if (hw->mac.type >= igc_i225 &&
	    !igc_get_flash_presence_i225(hw)) {
		return -EOPNOTSUPP;
	}

	if (eeprom->magic != (hw->vendor_id | (hw->device_id << 16)))
		return -EFAULT;

	max_len = hw->nvm.word_size * 2;

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;
	eeprom_buff = kmalloc(max_len, GFP_KERNEL);
	if (!eeprom_buff)
		return -ENOMEM;

	ptr = (void *)eeprom_buff;

	if (eeprom->offset & 1) {
		/* need read/modify/write of first changed EEPROM word
		 * only the second byte of the word is being modified
		 */
		ret_val = hw->nvm.ops.read(hw, first_word, 1,
					    &eeprom_buff[0]);
		ptr++;
	}
	if (((eeprom->offset + eeprom->len) & 1) && ret_val == 0) {
		/* need read/modify/write of last changed EEPROM word
		 * only the first byte of the word is being modified
		 */
		ret_val = hw->nvm.ops.read(hw, last_word, 1,
				   &eeprom_buff[last_word - first_word]);
	}

	/* Device's eeprom is always little-endian, word addressable */
	for (i = 0; i < last_word - first_word + 1; i++)
		le16_to_cpus(&eeprom_buff[i]);

	memcpy(ptr, bytes, eeprom->len);

	for (i = 0; i < last_word - first_word + 1; i++)
		eeprom_buff[i] = cpu_to_le16(eeprom_buff[i]);

	ret_val = hw->nvm.ops.write(hw, first_word,
				    last_word - first_word + 1, eeprom_buff);

	/* Update the checksum if nvm write succeeded */
	if (ret_val == 0)
		hw->nvm.ops.update(hw);

	/* check if need: igc_set_fw_version(adapter); */
	kfree(eeprom_buff);
	return ret_val;
}
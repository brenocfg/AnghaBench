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
typedef  int u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int magic; int offset; int /*<<< orphan*/  len; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_PF (struct bnxt*) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int bnxt_dir_type_is_executable (int) ; 
 int bnxt_erase_nvram_directory (struct net_device*,int) ; 
 int bnxt_flash_nvram (struct net_device*,int,int,int,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_set_eeprom(struct net_device *dev,
			   struct ethtool_eeprom *eeprom,
			   u8 *data)
{
	struct bnxt *bp = netdev_priv(dev);
	u8 index, dir_op;
	u16 type, ext, ordinal, attr;

	if (!BNXT_PF(bp)) {
		netdev_err(dev, "NVM write not supported from a virtual function\n");
		return -EINVAL;
	}

	type = eeprom->magic >> 16;

	if (type == 0xffff) { /* special value for directory operations */
		index = eeprom->magic & 0xff;
		dir_op = eeprom->magic >> 8;
		if (index == 0)
			return -EINVAL;
		switch (dir_op) {
		case 0x0e: /* erase */
			if (eeprom->offset != ~eeprom->magic)
				return -EINVAL;
			return bnxt_erase_nvram_directory(dev, index - 1);
		default:
			return -EINVAL;
		}
	}

	/* Create or re-write an NVM item: */
	if (bnxt_dir_type_is_executable(type) == true)
		return -EOPNOTSUPP;
	ext = eeprom->magic & 0xffff;
	ordinal = eeprom->offset >> 16;
	attr = eeprom->offset & 0xffff;

	return bnxt_flash_nvram(dev, type, ordinal, ext, attr, data,
				eeprom->len);
}
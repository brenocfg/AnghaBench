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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {scalar_t__ magic; int offset; int len; } ;
struct dev_priv {struct dev_info* adapter; } ;
struct dev_info {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 scalar_t__ EEPROM_MAGIC ; 
 int EEPROM_SIZE ; 
 int EINVAL ; 
 scalar_t__* eeprom_data ; 
 scalar_t__ eeprom_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eeprom_write (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netdev_set_eeprom(struct net_device *dev,
	struct ethtool_eeprom *eeprom, u8 *data)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	u16 eeprom_word[EEPROM_SIZE];
	u8 *eeprom_byte = (u8 *) eeprom_word;
	int i;
	int len;

	if (eeprom->magic != EEPROM_MAGIC)
		return -EINVAL;

	len = (eeprom->offset + eeprom->len + 1) / 2;
	for (i = eeprom->offset / 2; i < len; i++)
		eeprom_data[i] = eeprom_read(&hw_priv->hw, i);
	memcpy(eeprom_word, eeprom_data, EEPROM_SIZE * 2);
	memcpy(&eeprom_byte[eeprom->offset], data, eeprom->len);
	for (i = 0; i < EEPROM_SIZE; i++)
		if (eeprom_word[i] != eeprom_data[i]) {
			eeprom_data[i] = eeprom_word[i];
			eeprom_write(&hw_priv->hw, i, eeprom_data[i]);
	}

	return 0;
}
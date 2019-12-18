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
struct ethtool_eeprom {int offset; int len; int /*<<< orphan*/  magic; } ;
struct dev_priv {struct dev_info* adapter; } ;
struct dev_info {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_MAGIC ; 
 int /*<<< orphan*/ * eeprom_data ; 
 int /*<<< orphan*/  eeprom_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netdev_get_eeprom(struct net_device *dev,
	struct ethtool_eeprom *eeprom, u8 *data)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	u8 *eeprom_byte = (u8 *) eeprom_data;
	int i;
	int len;

	len = (eeprom->offset + eeprom->len + 1) / 2;
	for (i = eeprom->offset / 2; i < len; i++)
		eeprom_data[i] = eeprom_read(&hw_priv->hw, i);
	eeprom->magic = EEPROM_MAGIC;
	memcpy(data, &eeprom_byte[eeprom->offset], eeprom->len);

	return 0;
}
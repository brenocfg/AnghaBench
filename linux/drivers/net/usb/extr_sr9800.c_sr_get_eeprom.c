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
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int len; scalar_t__ offset; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SR_CMD_READ_EEPROM ; 
 int /*<<< orphan*/  SR_EEPROM_MAGIC ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int sr_read_cmd (struct usbnet*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sr_get_eeprom(struct net_device *net,
			      struct ethtool_eeprom *eeprom, u8 *data)
{
	struct usbnet *dev = netdev_priv(net);
	__le16 *ebuf = (__le16 *)data;
	int ret;
	int i;

	/* Crude hack to ensure that we don't overwrite memory
	 * if an odd length is supplied
	 */
	if (eeprom->len % 2)
		return -EINVAL;

	eeprom->magic = SR_EEPROM_MAGIC;

	/* sr9800 returns 2 bytes from eeprom on read */
	for (i = 0; i < eeprom->len / 2; i++) {
		ret = sr_read_cmd(dev, SR_CMD_READ_EEPROM, eeprom->offset + i,
				  0, 2, &ebuf[i]);
		if (ret < 0)
			return -EINVAL;
	}
	return 0;
}
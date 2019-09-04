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
struct port_info {int /*<<< orphan*/  tx_chan; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int offset; int len; } ;
struct adapter {int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_DEV_ADDR_A0 ; 
 int /*<<< orphan*/  I2C_DEV_ADDR_A2 ; 
 int I2C_PAGE_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t4_i2c_rd (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxgb4_get_module_eeprom(struct net_device *dev,
				   struct ethtool_eeprom *eprom, u8 *data)
{
	int ret = 0, offset = eprom->offset, len = eprom->len;
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;

	memset(data, 0, eprom->len);
	if (offset + len <= I2C_PAGE_SIZE)
		return t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan,
				 I2C_DEV_ADDR_A0, offset, len, data);

	/* offset + len spans 0xa0 and 0xa1 pages */
	if (offset <= I2C_PAGE_SIZE) {
		/* read 0xa0 page */
		len = I2C_PAGE_SIZE - offset;
		ret =  t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan,
				 I2C_DEV_ADDR_A0, offset, len, data);
		if (ret)
			return ret;
		offset = I2C_PAGE_SIZE;
		/* Remaining bytes to be read from second page =
		 * Total length - bytes read from first page
		 */
		len = eprom->len - len;
	}
	/* Read additional optical diagnostics from page 0xa2 if supported */
	return t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan, I2C_DEV_ADDR_A2,
			 offset, len, &data[eprom->len - len]);
}
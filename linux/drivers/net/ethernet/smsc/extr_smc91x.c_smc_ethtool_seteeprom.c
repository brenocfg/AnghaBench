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
struct ethtool_eeprom {int len; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,struct net_device*,char*,int,int,...) ; 
 int smc_ethtool_geteeprom_len (struct net_device*) ; 
 int smc_write_eeprom_word (struct net_device*,int,int) ; 

__attribute__((used)) static int smc_ethtool_seteeprom(struct net_device *dev,
		struct ethtool_eeprom *eeprom, u8 *data)
{
	int i;
	int imax;

	DBG(1, dev, "Writing %d bytes to %d(0x%x)\n",
	    eeprom->len, eeprom->offset, eeprom->offset);
	imax = smc_ethtool_geteeprom_len(dev);
	for (i = 0; i < eeprom->len; i += 2) {
		int ret;
		u16 wbuf;
		int offset = i + eeprom->offset;
		if (offset > imax)
			break;
		wbuf = (data[i] << 8) | data[i + 1];
		DBG(2, dev, "Writing 0x%x to 0x%x\n", wbuf, offset >> 1);
		ret = smc_write_eeprom_word(dev, offset >> 1, wbuf);
		if (ret != 0)
			return ret;
	}
	return 0;
}
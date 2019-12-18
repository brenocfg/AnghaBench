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
typedef  int u32 ;
struct r8192_priv {scalar_t__ epromtype; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ EEPROM_93C56 ; 
 int /*<<< orphan*/  EPROM_CMD ; 
 int EPROM_CMD_NORMAL ; 
 int EPROM_CMD_OPERATING_MODE_SHIFT ; 
 int EPROM_CMD_PROGRAM ; 
 int /*<<< orphan*/  EPROM_DELAY ; 
 int _rtl92e_eeprom_xfer (struct net_device*,int,int) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

u32 rtl92e_eeprom_read(struct net_device *dev, u32 addr)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	u32 ret = 0;

	rtl92e_writeb(dev, EPROM_CMD,
		      (EPROM_CMD_PROGRAM << EPROM_CMD_OPERATING_MODE_SHIFT));
	udelay(EPROM_DELAY);

	/* EEPROM is configured as x16 */
	if (priv->epromtype == EEPROM_93C56)
		ret = _rtl92e_eeprom_xfer(dev, (addr & 0xFF) | (0x6 << 8), 11);
	else
		ret = _rtl92e_eeprom_xfer(dev, (addr & 0x3F) | (0x6 << 6), 9);

	rtl92e_writeb(dev, EPROM_CMD,
		      (EPROM_CMD_NORMAL<<EPROM_CMD_OPERATING_MODE_SHIFT));
	return ret;
}
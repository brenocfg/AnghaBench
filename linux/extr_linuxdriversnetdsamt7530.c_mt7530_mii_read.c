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
typedef  int u16 ;
struct mt7530_priv {struct mii_bus* bus; } ;
struct mii_bus {int (* write ) (struct mii_bus*,int,int,int) ;int (* read ) (struct mii_bus*,int,int) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int stub1 (struct mii_bus*,int,int,int) ; 
 int stub2 (struct mii_bus*,int,int) ; 
 int stub3 (struct mii_bus*,int,int) ; 

__attribute__((used)) static u32
mt7530_mii_read(struct mt7530_priv *priv, u32 reg)
{
	struct mii_bus *bus = priv->bus;
	u16 page, r, lo, hi;
	int ret;

	page = (reg >> 6) & 0x3ff;
	r = (reg >> 2) & 0xf;

	/* MT7530 uses 31 as the pseudo port */
	ret = bus->write(bus, 0x1f, 0x1f, page);
	if (ret < 0) {
		dev_err(&bus->dev,
			"failed to read mt7530 register\n");
		return ret;
	}

	lo = bus->read(bus, 0x1f, r);
	hi = bus->read(bus, 0x1f, 0x10);

	return (hi << 16) | (lo & 0xffff);
}
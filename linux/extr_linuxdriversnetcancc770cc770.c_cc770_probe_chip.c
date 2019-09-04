#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct cc770_priv {int cpu_interface; int control_normal_mode; int /*<<< orphan*/  reg_base; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int CPUIF_RST ; 
 int CTRL_CCE ; 
 int CTRL_EAF ; 
 int CTRL_INI ; 
 int ENODEV ; 
 int cc770_read_reg (struct cc770_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc770_write_reg (struct cc770_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  cpu_interface ; 
 TYPE_1__* msgobj ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cc770_probe_chip(struct net_device *dev)
{
	struct cc770_priv *priv = netdev_priv(dev);

	/* Enable configuration, put chip in bus-off, disable ints */
	cc770_write_reg(priv, control, CTRL_CCE | CTRL_EAF | CTRL_INI);
	/* Configure cpu interface / CLKOUT disable */
	cc770_write_reg(priv, cpu_interface, priv->cpu_interface);

	/*
	 * Check if hardware reset is still inactive or maybe there
	 * is no chip in this address space
	 */
	if (cc770_read_reg(priv, cpu_interface) & CPUIF_RST) {
		netdev_info(dev, "probing @0x%p failed (reset)\n",
			    priv->reg_base);
		return -ENODEV;
	}

	/* Write and read back test pattern (some arbitrary values) */
	cc770_write_reg(priv, msgobj[1].data[1], 0x25);
	cc770_write_reg(priv, msgobj[2].data[3], 0x52);
	cc770_write_reg(priv, msgobj[10].data[6], 0xc3);
	if ((cc770_read_reg(priv, msgobj[1].data[1]) != 0x25) ||
	    (cc770_read_reg(priv, msgobj[2].data[3]) != 0x52) ||
	    (cc770_read_reg(priv, msgobj[10].data[6]) != 0xc3)) {
		netdev_info(dev, "probing @0x%p failed (pattern)\n",
			    priv->reg_base);
		return -ENODEV;
	}

	/* Check if this chip is a CC770 supporting additional functions */
	if (cc770_read_reg(priv, control) & CTRL_EAF)
		priv->control_normal_mode |= CTRL_EAF;

	return 0;
}
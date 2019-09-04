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
struct phy_device {int dummy; } ;
struct ksz_device {int dummy; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_MAC_LOOPBACK ; 
 int /*<<< orphan*/  REG_PORT_CTRL_0 ; 
 int /*<<< orphan*/  ksz_port_cfg (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ksz_disable_port(struct dsa_switch *ds, int port,
			     struct phy_device *phy)
{
	struct ksz_device *dev = ds->priv;

	/* there is no port disable */
	ksz_port_cfg(dev, port, REG_PORT_CTRL_0, PORT_MAC_LOOPBACK, true);
}
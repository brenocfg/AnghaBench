#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {int dummy; } ;
struct dsa_switch {struct dsa_loop_priv* priv; } ;
struct dsa_loop_priv {TYPE_2__* ports; scalar_t__ port_base; struct mii_bus* bus; } ;
struct TYPE_4__ {TYPE_1__* mib; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 size_t DSA_LOOP_PHY_WRITE_ERR ; 
 size_t DSA_LOOP_PHY_WRITE_OK ; 
 int mdiobus_write_nested (struct mii_bus*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_loop_phy_write(struct dsa_switch *ds, int port,
			      int regnum, u16 value)
{
	struct dsa_loop_priv *ps = ds->priv;
	struct mii_bus *bus = ps->bus;
	int ret;

	ret = mdiobus_write_nested(bus, ps->port_base + port, regnum, value);
	if (ret < 0)
		ps->ports[port].mib[DSA_LOOP_PHY_WRITE_ERR].val++;
	else
		ps->ports[port].mib[DSA_LOOP_PHY_WRITE_OK].val++;

	return ret;
}
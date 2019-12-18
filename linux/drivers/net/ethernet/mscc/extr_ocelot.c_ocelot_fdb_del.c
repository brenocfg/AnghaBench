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
typedef  int /*<<< orphan*/  u16 ;
struct ocelot_port {struct ocelot* ocelot; } ;
struct ocelot {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct ndmsg {int dummy; } ;

/* Variables and functions */
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int ocelot_mact_forget (struct ocelot*,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocelot_fdb_del(struct ndmsg *ndm, struct nlattr *tb[],
			  struct net_device *dev,
			  const unsigned char *addr, u16 vid)
{
	struct ocelot_port *port = netdev_priv(dev);
	struct ocelot *ocelot = port->ocelot;

	return ocelot_mact_forget(ocelot, addr, vid);
}
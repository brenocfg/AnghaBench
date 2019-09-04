#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct phy_device {int dummy; } ;
struct dsa_switch {TYPE_1__* ports; struct b53_device* priv; } ;
struct b53_device {TYPE_3__* ports; } ;
struct TYPE_8__ {unsigned int index; } ;
struct TYPE_6__ {scalar_t__ eee_enabled; } ;
struct TYPE_7__ {int vlan_ctl_mask; TYPE_2__ eee; } ;
struct TYPE_5__ {TYPE_4__* cpu_dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_PORT_CTRL (int) ; 
 int /*<<< orphan*/  B53_PVLAN_PAGE ; 
 int /*<<< orphan*/  B53_PVLAN_PORT_MASK (int) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  b53_eee_enable_set (struct dsa_switch*,int,int) ; 
 int /*<<< orphan*/  b53_imp_vlan_setup (struct dsa_switch*,unsigned int) ; 
 int /*<<< orphan*/  b53_read16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  b53_write16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int b53_enable_port(struct dsa_switch *ds, int port, struct phy_device *phy)
{
	struct b53_device *dev = ds->priv;
	unsigned int cpu_port = ds->ports[port].cpu_dp->index;
	u16 pvlan;

	/* Clear the Rx and Tx disable bits and set to no spanning tree */
	b53_write8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), 0);

	/* Set this port, and only this one to be in the default VLAN,
	 * if member of a bridge, restore its membership prior to
	 * bringing down this port.
	 */
	b53_read16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(port), &pvlan);
	pvlan &= ~0x1ff;
	pvlan |= BIT(port);
	pvlan |= dev->ports[port].vlan_ctl_mask;
	b53_write16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(port), pvlan);

	b53_imp_vlan_setup(ds, cpu_port);

	/* If EEE was enabled, restore it */
	if (dev->ports[port].eee.eee_enabled)
		b53_eee_enable_set(ds, port, true);

	return 0;
}
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
typedef  int u16 ;
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_LINK_STAT ; 
 int /*<<< orphan*/  B53_STAT_PAGE ; 
 int BIT (int) ; 
 int /*<<< orphan*/  b53_read16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dsa_port_phylink_mac_change (struct dsa_switch*,int,int) ; 

void b53_port_event(struct dsa_switch *ds, int port)
{
	struct b53_device *dev = ds->priv;
	bool link;
	u16 sts;

	b53_read16(dev, B53_STAT_PAGE, B53_LINK_STAT, &sts);
	link = !!(sts & BIT(port));
	dsa_port_phylink_mac_change(ds, port, link);
}
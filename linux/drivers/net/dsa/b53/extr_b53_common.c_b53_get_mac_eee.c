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
typedef  int u16 ;
struct ethtool_eee {int eee_active; int /*<<< orphan*/  eee_enabled; } ;
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {TYPE_1__* ports; } ;
struct TYPE_2__ {struct ethtool_eee eee; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_EEE_LPI_INDICATE ; 
 int /*<<< orphan*/  B53_EEE_PAGE ; 
 int BIT (int) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  b53_read16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ is5325 (struct b53_device*) ; 
 scalar_t__ is5365 (struct b53_device*) ; 

int b53_get_mac_eee(struct dsa_switch *ds, int port, struct ethtool_eee *e)
{
	struct b53_device *dev = ds->priv;
	struct ethtool_eee *p = &dev->ports[port].eee;
	u16 reg;

	if (is5325(dev) || is5365(dev))
		return -EOPNOTSUPP;

	b53_read16(dev, B53_EEE_PAGE, B53_EEE_LPI_INDICATE, &reg);
	e->eee_enabled = p->eee_enabled;
	e->eee_active = !!(reg & BIT(port));

	return 0;
}
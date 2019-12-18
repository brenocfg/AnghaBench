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
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* serdes_an_restart ) (struct b53_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct b53_device*,int) ; 

void b53_phylink_mac_an_restart(struct dsa_switch *ds, int port)
{
	struct b53_device *dev = ds->priv;

	if (dev->ops->serdes_an_restart)
		dev->ops->serdes_an_restart(dev, port);
}
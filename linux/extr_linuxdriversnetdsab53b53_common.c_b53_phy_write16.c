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
typedef  int /*<<< orphan*/  u16 ;
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* phy_write16 ) (struct b53_device*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B53_PORT_MII_PAGE (int) ; 
 int b53_write16 (struct b53_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct b53_device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b53_phy_write16(struct dsa_switch *ds, int addr, int reg, u16 val)
{
	struct b53_device *priv = ds->priv;

	if (priv->ops->phy_write16)
		return priv->ops->phy_write16(priv, addr, reg, val);

	return b53_write16(priv, B53_PORT_MII_PAGE(addr), reg * 2, val);
}
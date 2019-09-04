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
typedef  int /*<<< orphan*/  u32 ;
struct mt7530_priv {struct mii_bus* bus; } ;
struct mii_bus {int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_VEND2 ; 
 int /*<<< orphan*/  MDIO_MUTEX_NESTED ; 
 int /*<<< orphan*/  core_read_mmd_indirect (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_write_mmd_indirect (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
core_rmw(struct mt7530_priv *priv, u32 reg, u32 mask, u32 set)
{
	struct mii_bus *bus = priv->bus;
	u32 val;

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	val = core_read_mmd_indirect(priv, reg, MDIO_MMD_VEND2);
	val &= ~mask;
	val |= set;
	core_write_mmd_indirect(priv, reg, MDIO_MMD_VEND2, val);

	mutex_unlock(&bus->mdio_lock);
}
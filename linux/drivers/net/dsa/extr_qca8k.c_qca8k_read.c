#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct qca8k_priv {TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MUTEX_NESTED ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qca8k_mii_read32 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  qca8k_set_page (TYPE_1__*,int) ; 
 int /*<<< orphan*/  qca8k_split_addr (int /*<<< orphan*/ ,int*,int*,int*) ; 

__attribute__((used)) static u32
qca8k_read(struct qca8k_priv *priv, u32 reg)
{
	u16 r1, r2, page;
	u32 val;

	qca8k_split_addr(reg, &r1, &r2, &page);

	mutex_lock_nested(&priv->bus->mdio_lock, MDIO_MUTEX_NESTED);

	qca8k_set_page(priv->bus, page);
	val = qca8k_mii_read32(priv->bus, 0x10 | r2, r1);

	mutex_unlock(&priv->bus->mdio_lock);

	return val;
}
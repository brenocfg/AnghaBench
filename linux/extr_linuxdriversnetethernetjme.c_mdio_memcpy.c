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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct jme_adapter {TYPE_1__ mii_if; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  jme_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mdio_memcpy(struct jme_adapter *jme, u32 *p, int reg_nr)
{
	int i;
	u16 *p16 = (u16 *)p;

	for (i = 0 ; i < reg_nr ; ++i)
		p16[i] = jme_mdio_read(jme->dev, jme->mii_if.phy_id, i);
}
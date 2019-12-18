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
struct TYPE_2__ {int (* mdio_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  prtad; int /*<<< orphan*/  dev; } ;
struct cphy {TYPE_1__ mdio; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int t3_mdio_read(struct cphy *phy, int mmd, int reg,
			       unsigned int *valp)
{
	int rc = phy->mdio.mdio_read(phy->mdio.dev, phy->mdio.prtad, mmd, reg);
	*valp = (rc >= 0) ? rc : -1;
	return (rc >= 0) ? 0 : rc;
}
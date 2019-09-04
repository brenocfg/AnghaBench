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
struct TYPE_2__ {int (* mdio_write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ;int /*<<< orphan*/  prtad; int /*<<< orphan*/  dev; } ;
struct cphy {TYPE_1__ mdio; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 

__attribute__((used)) static inline int cphy_mdio_write(struct cphy *cphy, int mmd, int reg,
				  unsigned int val)
{
	return cphy->mdio.mdio_write(cphy->mdio.dev, cphy->mdio.prtad, mmd,
				     reg, val);
}
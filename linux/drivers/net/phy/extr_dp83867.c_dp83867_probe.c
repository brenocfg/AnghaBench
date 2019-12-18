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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {struct dp83867_private* priv; TYPE_1__ mdio; } ;
struct dp83867_private {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dp83867_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dp83867_probe(struct phy_device *phydev)
{
	struct dp83867_private *dp83867;

	dp83867 = devm_kzalloc(&phydev->mdio.dev, sizeof(*dp83867),
			       GFP_KERNEL);
	if (!dp83867)
		return -ENOMEM;

	phydev->priv = dp83867;

	return 0;
}
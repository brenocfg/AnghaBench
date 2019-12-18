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
struct serdes_am654 {int /*<<< orphan*/  por_en; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 struct serdes_am654* phy_get_drvdata (struct phy*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int serdes_am654_reset(struct phy *x)
{
	struct serdes_am654 *phy = phy_get_drvdata(x);
	int ret;

	ret = regmap_field_write(phy->por_en, 0x1);
	if (ret)
		return ret;

	mdelay(1);

	ret = regmap_field_write(phy->por_en, 0x0);
	if (ret)
		return ret;

	return 0;
}
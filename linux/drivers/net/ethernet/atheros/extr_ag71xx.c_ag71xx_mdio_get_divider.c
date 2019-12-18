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
typedef  unsigned long u32 ;
struct ag71xx {int /*<<< orphan*/  clk_mdio; } ;

/* Variables and functions */
 unsigned long AG71XX_MDIO_MAX_CLK ; 
 int /*<<< orphan*/  AR7240 ; 
 int /*<<< orphan*/  AR9330 ; 
 int /*<<< orphan*/  AR9340 ; 
 int ARRAY_SIZE (unsigned long*) ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ ag71xx_is (struct ag71xx*,int /*<<< orphan*/ ) ; 
 unsigned long* ar71xx_mdio_div_table ; 
 unsigned long* ar7240_mdio_div_table ; 
 unsigned long* ar933x_mdio_div_table ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ag71xx_mdio_get_divider(struct ag71xx *ag, u32 *div)
{
	unsigned long ref_clock;
	const u32 *table;
	int ndivs, i;

	ref_clock = clk_get_rate(ag->clk_mdio);
	if (!ref_clock)
		return -EINVAL;

	if (ag71xx_is(ag, AR9330) || ag71xx_is(ag, AR9340)) {
		table = ar933x_mdio_div_table;
		ndivs = ARRAY_SIZE(ar933x_mdio_div_table);
	} else if (ag71xx_is(ag, AR7240)) {
		table = ar7240_mdio_div_table;
		ndivs = ARRAY_SIZE(ar7240_mdio_div_table);
	} else {
		table = ar71xx_mdio_div_table;
		ndivs = ARRAY_SIZE(ar71xx_mdio_div_table);
	}

	for (i = 0; i < ndivs; i++) {
		unsigned long t;

		t = ref_clock / table[i];
		if (t <= AG71XX_MDIO_MAX_CLK) {
			*div = i;
			return 0;
		}
	}

	return -ENOENT;
}
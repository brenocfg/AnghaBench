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
struct serdes_am654 {int /*<<< orphan*/  pll_ok; int /*<<< orphan*/  pll_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_ENABLE_STATE ; 
 int /*<<< orphan*/  PLL_LOCK_TIME ; 
 int regmap_field_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serdes_am654_enable_pll(struct serdes_am654 *phy)
{
	int ret;
	u32 val;

	ret = regmap_field_write(phy->pll_enable, PLL_ENABLE_STATE);
	if (ret)
		return ret;

	return regmap_field_read_poll_timeout(phy->pll_ok, val, val, 1000,
					      PLL_LOCK_TIME);
}
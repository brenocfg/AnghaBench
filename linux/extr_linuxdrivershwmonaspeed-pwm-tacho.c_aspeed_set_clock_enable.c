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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_PTCR_CTRL ; 
 int /*<<< orphan*/  ASPEED_PTCR_CTRL_CLK_EN ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspeed_set_clock_enable(struct regmap *regmap, bool val)
{
	regmap_update_bits(regmap, ASPEED_PTCR_CTRL,
			   ASPEED_PTCR_CTRL_CLK_EN,
			   val ? ASPEED_PTCR_CTRL_CLK_EN : 0);
}
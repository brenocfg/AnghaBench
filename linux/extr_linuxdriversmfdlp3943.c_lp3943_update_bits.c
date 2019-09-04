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
typedef  int /*<<< orphan*/  u8 ;
struct lp3943 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lp3943_update_bits(struct lp3943 *lp3943, u8 reg, u8 mask, u8 data)
{
	return regmap_update_bits(lp3943->regmap, reg, mask, data);
}
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
struct clk_si544 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI544_OE_STATE_ODC_OE ; 
 int /*<<< orphan*/  SI544_REG_OE_STATE ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si544_enable_output(struct clk_si544 *data, bool enable)
{
	return regmap_update_bits(data->regmap, SI544_REG_OE_STATE,
		SI544_OE_STATE_ODC_OE, enable ? SI544_OE_STATE_ODC_OE : 0);
}
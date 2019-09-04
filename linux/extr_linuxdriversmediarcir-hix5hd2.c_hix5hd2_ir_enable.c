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
struct hix5hd2_ir_priv {int /*<<< orphan*/  clock; scalar_t__ regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IR_CLK ; 
 int /*<<< orphan*/  IR_CLK_ENABLE ; 
 int /*<<< orphan*/  IR_CLK_RESET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hix5hd2_ir_enable(struct hix5hd2_ir_priv *dev, bool on)
{
	u32 val;
	int ret = 0;

	if (dev->regmap) {
		regmap_read(dev->regmap, IR_CLK, &val);
		if (on) {
			val &= ~IR_CLK_RESET;
			val |= IR_CLK_ENABLE;
		} else {
			val &= ~IR_CLK_ENABLE;
			val |= IR_CLK_RESET;
		}
		regmap_write(dev->regmap, IR_CLK, val);
	} else {
		if (on)
			ret = clk_prepare_enable(dev->clock);
		else
			clk_disable_unprepare(dev->clock);
	}
	return ret;
}
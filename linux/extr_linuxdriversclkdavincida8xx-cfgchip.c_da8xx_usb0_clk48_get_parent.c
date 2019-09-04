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
typedef  int u8 ;
struct da8xx_usb0_clk48 {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFGCHIP (int) ; 
 unsigned int CFGCHIP2_USB2PHYCLKMUX ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct da8xx_usb0_clk48* to_da8xx_usb0_clk48 (struct clk_hw*) ; 

__attribute__((used)) static u8 da8xx_usb0_clk48_get_parent(struct clk_hw *hw)
{
	struct da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);
	unsigned int val;

	regmap_read(usb0->regmap, CFGCHIP(2), &val);

	return (val & CFGCHIP2_USB2PHYCLKMUX) ? 1 : 0;
}
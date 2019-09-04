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
struct cs2000_priv {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs2000_clk_out_enable (struct cs2000_priv*,int) ; 
 int /*<<< orphan*/  cs2000_enable_dev_config (struct cs2000_priv*,int) ; 
 struct cs2000_priv* hw_to_priv (struct clk_hw*) ; 

__attribute__((used)) static void cs2000_disable(struct clk_hw *hw)
{
	struct cs2000_priv *priv = hw_to_priv(hw);

	cs2000_enable_dev_config(priv, false);

	cs2000_clk_out_enable(priv, false);
}
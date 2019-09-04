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
struct device {int dummy; } ;
struct clk_hw {int dummy; } ;
typedef  struct clk_hw clk ;
struct TYPE_2__ {struct clk_hw** hws; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct clk_hw*) ; 
 int PTR_ERR (struct clk_hw*) ; 
 int /*<<< orphan*/  __clk_get_name (struct clk_hw*) ; 
 TYPE_1__ axg_audio_hw_onecell_data ; 
 struct clk_hw* axg_clk_hw_register_bypass (struct device*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*) ; 
 struct clk_hw* devm_clk_get (struct device*,char const*) ; 

__attribute__((used)) static int axg_register_clk_hw_input(struct device *dev,
				     const char *name,
				     unsigned int clkid)
{
	struct clk *parent_clk = devm_clk_get(dev, name);
	struct clk_hw *hw = NULL;

	if (IS_ERR(parent_clk)) {
		int err = PTR_ERR(parent_clk);

		/* It is ok if an input clock is missing */
		if (err == -ENOENT) {
			dev_dbg(dev, "%s not provided", name);
		} else {
			if (err != -EPROBE_DEFER)
				dev_err(dev, "failed to get %s clock", name);
			return err;
		}
	} else {
		hw = axg_clk_hw_register_bypass(dev, name,
						__clk_get_name(parent_clk));
	}

	if (IS_ERR(hw)) {
		dev_err(dev, "failed to register %s clock", name);
		return PTR_ERR(hw);
	}

	axg_audio_hw_onecell_data.hws[clkid] = hw;
	return 0;
}
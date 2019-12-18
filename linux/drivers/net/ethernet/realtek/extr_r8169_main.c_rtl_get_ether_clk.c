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
struct rtl8169_private {struct clk* clk; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct clk*) ; 
 struct clk* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  rtl_disable_clk ; 
 struct device* tp_to_dev (struct rtl8169_private*) ; 

__attribute__((used)) static int rtl_get_ether_clk(struct rtl8169_private *tp)
{
	struct device *d = tp_to_dev(tp);
	struct clk *clk;
	int rc;

	clk = devm_clk_get(d, "ether_clk");
	if (IS_ERR(clk)) {
		rc = PTR_ERR(clk);
		if (rc == -ENOENT)
			/* clk-core allows NULL (for suspend / resume) */
			rc = 0;
		else if (rc != -EPROBE_DEFER)
			dev_err(d, "failed to get clk: %d\n", rc);
	} else {
		tp->clk = clk;
		rc = clk_prepare_enable(clk);
		if (rc)
			dev_err(d, "failed to enable clk: %d\n", rc);
		else
			rc = devm_add_action_or_reset(d, rtl_disable_clk, clk);
	}

	return rc;
}
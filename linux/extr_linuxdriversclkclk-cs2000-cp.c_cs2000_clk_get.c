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
struct device {int dummy; } ;
struct cs2000_priv {struct clk* ref_clk; struct clk* clk_in; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 struct clk* devm_clk_get (struct device*,char*) ; 
 struct device* priv_to_dev (struct cs2000_priv*) ; 

__attribute__((used)) static int cs2000_clk_get(struct cs2000_priv *priv)
{
	struct device *dev = priv_to_dev(priv);
	struct clk *clk_in, *ref_clk;

	clk_in = devm_clk_get(dev, "clk_in");
	/* not yet provided */
	if (IS_ERR(clk_in))
		return -EPROBE_DEFER;

	ref_clk = devm_clk_get(dev, "ref_clk");
	/* not yet provided */
	if (IS_ERR(ref_clk))
		return -EPROBE_DEFER;

	priv->clk_in	= clk_in;
	priv->ref_clk	= ref_clk;

	return 0;
}
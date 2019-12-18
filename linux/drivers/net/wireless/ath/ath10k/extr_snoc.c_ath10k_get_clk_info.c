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
struct clk {int dummy; } ;
struct ath10k_clk_info {int freq; struct clk* handle; int /*<<< orphan*/  name; scalar_t__ required; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SNOC ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 struct clk* devm_clk_get (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_get_clk_info(struct ath10k *ar, struct device *dev,
			       struct ath10k_clk_info *clk_info)
{
	struct clk *handle;
	int ret = 0;

	handle = devm_clk_get(dev, clk_info->name);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		if (clk_info->required) {
			ath10k_err(ar, "snoc clock %s isn't available: %d\n",
				   clk_info->name, ret);
			return ret;
		}
		ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc ignoring clock %s: %d\n",
			   clk_info->name,
			   ret);
		return 0;
	}

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc clock %s freq %u\n",
		   clk_info->name, clk_info->freq);

	clk_info->handle = handle;

	return ret;
}
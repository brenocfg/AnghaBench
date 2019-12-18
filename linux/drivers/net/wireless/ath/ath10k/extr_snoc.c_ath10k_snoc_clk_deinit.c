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
struct ath10k_snoc {struct ath10k_clk_info* clk; } ;
struct ath10k_clk_info {int /*<<< orphan*/  handle; int /*<<< orphan*/  name; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH10K_DBG_SNOC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  clk_cfg ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_snoc_clk_deinit(struct ath10k *ar)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	struct ath10k_clk_info *clk_info;
	int i;

	for (i = 0; i < ARRAY_SIZE(clk_cfg); i++) {
		clk_info = &ar_snoc->clk[i];

		if (!clk_info->handle)
			continue;

		ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc clock %s being disabled\n",
			   clk_info->name);

		clk_disable_unprepare(clk_info->handle);
	}

	return 0;
}
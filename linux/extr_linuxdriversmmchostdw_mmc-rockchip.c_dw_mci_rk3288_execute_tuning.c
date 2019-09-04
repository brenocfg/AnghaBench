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
struct mmc_host {int dummy; } ;
struct dw_mci_slot {struct mmc_host* mmc; struct dw_mci* host; } ;
struct dw_mci_rockchip_priv_data {int num_phases; int /*<<< orphan*/  sample_clk; int /*<<< orphan*/  default_sample_phase; } ;
struct dw_mci {int /*<<< orphan*/  dev; struct dw_mci_rockchip_priv_data* priv; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TUNING_ITERATION_TO_PHASE (int,int) ; 
 int /*<<< orphan*/  clk_set_phase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct range_t*) ; 
 struct range_t* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_send_tuning (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw_mci_rk3288_execute_tuning(struct dw_mci_slot *slot, u32 opcode)
{
	struct dw_mci *host = slot->host;
	struct dw_mci_rockchip_priv_data *priv = host->priv;
	struct mmc_host *mmc = slot->mmc;
	int ret = 0;
	int i;
	bool v, prev_v = 0, first_v;
	struct range_t {
		int start;
		int end; /* inclusive */
	};
	struct range_t *ranges;
	unsigned int range_count = 0;
	int longest_range_len = -1;
	int longest_range = -1;
	int middle_phase;

	if (IS_ERR(priv->sample_clk)) {
		dev_err(host->dev, "Tuning clock (sample_clk) not defined.\n");
		return -EIO;
	}

	ranges = kmalloc_array(priv->num_phases / 2 + 1,
			       sizeof(*ranges), GFP_KERNEL);
	if (!ranges)
		return -ENOMEM;

	/* Try each phase and extract good ranges */
	for (i = 0; i < priv->num_phases; ) {
		clk_set_phase(priv->sample_clk,
			      TUNING_ITERATION_TO_PHASE(i, priv->num_phases));

		v = !mmc_send_tuning(mmc, opcode, NULL);

		if (i == 0)
			first_v = v;

		if ((!prev_v) && v) {
			range_count++;
			ranges[range_count-1].start = i;
		}
		if (v) {
			ranges[range_count-1].end = i;
			i++;
		} else if (i == priv->num_phases - 1) {
			/* No extra skipping rules if we're at the end */
			i++;
		} else {
			/*
			 * No need to check too close to an invalid
			 * one since testing bad phases is slow.  Skip
			 * 20 degrees.
			 */
			i += DIV_ROUND_UP(20 * priv->num_phases, 360);

			/* Always test the last one */
			if (i >= priv->num_phases)
				i = priv->num_phases - 1;
		}

		prev_v = v;
	}

	if (range_count == 0) {
		dev_warn(host->dev, "All phases bad!");
		ret = -EIO;
		goto free;
	}

	/* wrap around case, merge the end points */
	if ((range_count > 1) && first_v && v) {
		ranges[0].start = ranges[range_count-1].start;
		range_count--;
	}

	if (ranges[0].start == 0 && ranges[0].end == priv->num_phases - 1) {
		clk_set_phase(priv->sample_clk, priv->default_sample_phase);
		dev_info(host->dev, "All phases work, using default phase %d.",
			 priv->default_sample_phase);
		goto free;
	}

	/* Find the longest range */
	for (i = 0; i < range_count; i++) {
		int len = (ranges[i].end - ranges[i].start + 1);

		if (len < 0)
			len += priv->num_phases;

		if (longest_range_len < len) {
			longest_range_len = len;
			longest_range = i;
		}

		dev_dbg(host->dev, "Good phase range %d-%d (%d len)\n",
			TUNING_ITERATION_TO_PHASE(ranges[i].start,
						  priv->num_phases),
			TUNING_ITERATION_TO_PHASE(ranges[i].end,
						  priv->num_phases),
			len
		);
	}

	dev_dbg(host->dev, "Best phase range %d-%d (%d len)\n",
		TUNING_ITERATION_TO_PHASE(ranges[longest_range].start,
					  priv->num_phases),
		TUNING_ITERATION_TO_PHASE(ranges[longest_range].end,
					  priv->num_phases),
		longest_range_len
	);

	middle_phase = ranges[longest_range].start + longest_range_len / 2;
	middle_phase %= priv->num_phases;
	dev_info(host->dev, "Successfully tuned phase to %d\n",
		 TUNING_ITERATION_TO_PHASE(middle_phase, priv->num_phases));

	clk_set_phase(priv->sample_clk,
		      TUNING_ITERATION_TO_PHASE(middle_phase,
						priv->num_phases));

free:
	kfree(ranges);
	return ret;
}
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
struct rproc {int bootaddr; struct q6v5_wcss* priv; } ;
struct q6v5_wcss {int /*<<< orphan*/  wcss_reset; int /*<<< orphan*/  wcss_q6_reset; int /*<<< orphan*/  dev; int /*<<< orphan*/  q6v5; scalar_t__ reg_base; scalar_t__ halt_nc; int /*<<< orphan*/  halt_map; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 scalar_t__ Q6SS_RST_EVB ; 
 scalar_t__ TCSR_GLOBAL_CFG0 ; 
 scalar_t__ TCSR_GLOBAL_CFG1 ; 
 int /*<<< orphan*/  TCSR_WCSS_CLK_ENABLE ; 
 int TCSR_WCSS_CLK_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int q6v5_wcss_reset (struct q6v5_wcss*) ; 
 int /*<<< orphan*/  qcom_q6v5_prepare (int /*<<< orphan*/ *) ; 
 int qcom_q6v5_wait_for_start (int /*<<< orphan*/ *,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int q6v5_wcss_start(struct rproc *rproc)
{
	struct q6v5_wcss *wcss = rproc->priv;
	int ret;

	qcom_q6v5_prepare(&wcss->q6v5);

	/* Release Q6 and WCSS reset */
	ret = reset_control_deassert(wcss->wcss_reset);
	if (ret) {
		dev_err(wcss->dev, "wcss_reset failed\n");
		return ret;
	}

	ret = reset_control_deassert(wcss->wcss_q6_reset);
	if (ret) {
		dev_err(wcss->dev, "wcss_q6_reset failed\n");
		goto wcss_reset;
	}

	/* Lithium configuration - clock gating and bus arbitration */
	ret = regmap_update_bits(wcss->halt_map,
				 wcss->halt_nc + TCSR_GLOBAL_CFG0,
				 TCSR_WCSS_CLK_MASK,
				 TCSR_WCSS_CLK_ENABLE);
	if (ret)
		goto wcss_q6_reset;

	ret = regmap_update_bits(wcss->halt_map,
				 wcss->halt_nc + TCSR_GLOBAL_CFG1,
				 1, 0);
	if (ret)
		goto wcss_q6_reset;

	/* Write bootaddr to EVB so that Q6WCSS will jump there after reset */
	writel(rproc->bootaddr >> 4, wcss->reg_base + Q6SS_RST_EVB);

	ret = q6v5_wcss_reset(wcss);
	if (ret)
		goto wcss_q6_reset;

	ret = qcom_q6v5_wait_for_start(&wcss->q6v5, 5 * HZ);
	if (ret == -ETIMEDOUT)
		dev_err(wcss->dev, "start timed out\n");

	return ret;

wcss_q6_reset:
	reset_control_assert(wcss->wcss_q6_reset);

wcss_reset:
	reset_control_assert(wcss->wcss_reset);

	return ret;
}
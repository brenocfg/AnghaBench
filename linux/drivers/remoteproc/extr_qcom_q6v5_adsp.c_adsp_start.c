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
struct rproc {scalar_t__ priv; } ;
struct qcom_adsp {int mem_phys; int /*<<< orphan*/  q6v5; int /*<<< orphan*/  xo; int /*<<< orphan*/  dev; int /*<<< orphan*/  clks; int /*<<< orphan*/  num_clks; scalar_t__ qdsp6ss_base; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ BOOT_CMD_REG ; 
 int /*<<< orphan*/  BOOT_FSM_TIMEOUT ; 
 scalar_t__ BOOT_STATUS_REG ; 
 scalar_t__ CORE_START_REG ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ QDSP6SS_CORE_CBCR ; 
 scalar_t__ QDSP6SS_SLEEP_CBCR ; 
 scalar_t__ QDSP6SS_XO_CBCR ; 
 scalar_t__ RST_EVB_REG ; 
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_bulk_prepare_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_pm_genpd_set_performance_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_q6v5_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_q6v5_unprepare (int /*<<< orphan*/ *) ; 
 int qcom_q6v5_wait_for_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int readl_poll_timeout (scalar_t__,unsigned int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int adsp_start(struct rproc *rproc)
{
	struct qcom_adsp *adsp = (struct qcom_adsp *)rproc->priv;
	int ret;
	unsigned int val;

	qcom_q6v5_prepare(&adsp->q6v5);

	ret = clk_prepare_enable(adsp->xo);
	if (ret)
		goto disable_irqs;

	dev_pm_genpd_set_performance_state(adsp->dev, INT_MAX);
	ret = pm_runtime_get_sync(adsp->dev);
	if (ret)
		goto disable_xo_clk;

	ret = clk_bulk_prepare_enable(adsp->num_clks, adsp->clks);
	if (ret) {
		dev_err(adsp->dev, "adsp clk_enable failed\n");
		goto disable_power_domain;
	}

	/* Enable the XO clock */
	writel(1, adsp->qdsp6ss_base + QDSP6SS_XO_CBCR);

	/* Enable the QDSP6SS sleep clock */
	writel(1, adsp->qdsp6ss_base + QDSP6SS_SLEEP_CBCR);

	/* Enable the QDSP6 core clock */
	writel(1, adsp->qdsp6ss_base + QDSP6SS_CORE_CBCR);

	/* Program boot address */
	writel(adsp->mem_phys >> 4, adsp->qdsp6ss_base + RST_EVB_REG);

	/* De-assert QDSP6 stop core. QDSP6 will execute after out of reset */
	writel(0x1, adsp->qdsp6ss_base + CORE_START_REG);

	/* Trigger boot FSM to start QDSP6 */
	writel(0x1, adsp->qdsp6ss_base + BOOT_CMD_REG);

	/* Wait for core to come out of reset */
	ret = readl_poll_timeout(adsp->qdsp6ss_base + BOOT_STATUS_REG,
			val, (val & BIT(0)) != 0, 10, BOOT_FSM_TIMEOUT);
	if (ret) {
		dev_err(adsp->dev, "failed to bootup adsp\n");
		goto disable_adsp_clks;
	}

	ret = qcom_q6v5_wait_for_start(&adsp->q6v5, msecs_to_jiffies(5 * HZ));
	if (ret == -ETIMEDOUT) {
		dev_err(adsp->dev, "start timed out\n");
		goto disable_adsp_clks;
	}

	return 0;

disable_adsp_clks:
	clk_bulk_disable_unprepare(adsp->num_clks, adsp->clks);
disable_power_domain:
	dev_pm_genpd_set_performance_state(adsp->dev, 0);
	pm_runtime_put(adsp->dev);
disable_xo_clk:
	clk_disable_unprepare(adsp->xo);
disable_irqs:
	qcom_q6v5_unprepare(&adsp->q6v5);

	return ret;
}
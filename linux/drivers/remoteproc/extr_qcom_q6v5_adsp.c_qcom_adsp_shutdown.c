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
struct qcom_adsp {int /*<<< orphan*/  restart; int /*<<< orphan*/  pdc_sync_reset; scalar_t__ halt_lpass; int /*<<< orphan*/  halt_map; int /*<<< orphan*/  dev; int /*<<< orphan*/  clks; int /*<<< orphan*/  num_clks; scalar_t__ qdsp6ss_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_TIMEOUT ; 
 scalar_t__ LPASS_HALTACK_REG ; 
 scalar_t__ LPASS_HALTREQ_REG ; 
 scalar_t__ LPASS_MASTER_IDLE_REG ; 
 scalar_t__ LPASS_PWR_ON_REG ; 
 scalar_t__ RET_CFG_REG ; 
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int qcom_adsp_shutdown(struct qcom_adsp *adsp)
{
	unsigned long timeout;
	unsigned int val;
	int ret;

	/* Reset the retention logic */
	val = readl(adsp->qdsp6ss_base + RET_CFG_REG);
	val |= 0x1;
	writel(val, adsp->qdsp6ss_base + RET_CFG_REG);

	clk_bulk_disable_unprepare(adsp->num_clks, adsp->clks);

	/* QDSP6 master port needs to be explicitly halted */
	ret = regmap_read(adsp->halt_map,
			adsp->halt_lpass + LPASS_PWR_ON_REG, &val);
	if (ret || !val)
		goto reset;

	ret = regmap_read(adsp->halt_map,
			adsp->halt_lpass + LPASS_MASTER_IDLE_REG,
			&val);
	if (ret || val)
		goto reset;

	regmap_write(adsp->halt_map,
			adsp->halt_lpass + LPASS_HALTREQ_REG, 1);

	/* Wait for halt ACK from QDSP6 */
	timeout = jiffies + msecs_to_jiffies(ACK_TIMEOUT);
	for (;;) {
		ret = regmap_read(adsp->halt_map,
			adsp->halt_lpass + LPASS_HALTACK_REG, &val);
		if (ret || val || time_after(jiffies, timeout))
			break;

		usleep_range(1000, 1100);
	}

	ret = regmap_read(adsp->halt_map,
			adsp->halt_lpass + LPASS_MASTER_IDLE_REG, &val);
	if (ret || !val)
		dev_err(adsp->dev, "port failed halt\n");

reset:
	/* Assert the LPASS PDC Reset */
	reset_control_assert(adsp->pdc_sync_reset);
	/* Place the LPASS processor into reset */
	reset_control_assert(adsp->restart);
	/* wait after asserting subsystem restart from AOSS */
	usleep_range(200, 300);

	/* Clear the halt request for the AXIM and AHBM for Q6 */
	regmap_write(adsp->halt_map, adsp->halt_lpass + LPASS_HALTREQ_REG, 0);

	/* De-assert the LPASS PDC Reset */
	reset_control_deassert(adsp->pdc_sync_reset);
	/* Remove the LPASS reset */
	reset_control_deassert(adsp->restart);
	/* wait after de-asserting subsystem restart from AOSS */
	usleep_range(200, 300);

	return 0;
}
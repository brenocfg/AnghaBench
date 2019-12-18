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
typedef  int u8 ;
typedef  int u32 ;
struct phy {int dummy; } ;
struct exynos_sata_phy {TYPE_1__* phy; scalar_t__ regs; int /*<<< orphan*/  client; int /*<<< orphan*/  pmureg; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTRL0_P0_PHY_CALIBRATED ; 
 int CTRL0_P0_PHY_CALIBRATED_SEL ; 
 int /*<<< orphan*/  EXYNOS5_SATAPHY_PMU_ENABLE ; 
 scalar_t__ EXYNOS5_SATA_CTRL0 ; 
 scalar_t__ EXYNOS5_SATA_MODE0 ; 
 scalar_t__ EXYNOS5_SATA_PHSATA_CTRLM ; 
 int /*<<< orphan*/  EXYNOS5_SATA_PHSATA_STATM ; 
 scalar_t__ EXYNOS5_SATA_RESET ; 
 int LINK_RESET ; 
 int PHCTRLM_HIGH_SPEED ; 
 int PHCTRLM_REF_RATE ; 
 int /*<<< orphan*/  PHSTATM_PLL_LOCKED ; 
 int RESET_CMN_BLOCK_RST_N ; 
 int RESET_CMN_I2C_RST_N ; 
 int RESET_CMN_RST_N ; 
 int RESET_GLOBAL_RST_N ; 
 int RESET_TX_RX_BLOCK_RST_N ; 
 int RESET_TX_RX_I2C_RST_N ; 
 int RESET_TX_RX_PIPE_RST_N ; 
 int /*<<< orphan*/  SATAPHY_CONTROL_OFFSET ; 
 int SATA_SPD_GEN3 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 
 struct exynos_sata_phy* phy_get_drvdata (struct phy*) ; 
 int readl (scalar_t__) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wait_for_reg_status (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int exynos_sata_phy_init(struct phy *phy)
{
	u32 val = 0;
	int ret = 0;
	u8 buf[] = { 0x3a, 0x0b };
	struct exynos_sata_phy *sata_phy = phy_get_drvdata(phy);

	ret = regmap_update_bits(sata_phy->pmureg, SATAPHY_CONTROL_OFFSET,
			EXYNOS5_SATAPHY_PMU_ENABLE, true);
	if (ret != 0)
		dev_err(&sata_phy->phy->dev, "phy init failed\n");

	writel(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	val = readl(sata_phy->regs + EXYNOS5_SATA_RESET);
	val |= RESET_GLOBAL_RST_N | RESET_CMN_RST_N | RESET_CMN_BLOCK_RST_N
		| RESET_CMN_I2C_RST_N | RESET_TX_RX_PIPE_RST_N
		| RESET_TX_RX_BLOCK_RST_N | RESET_TX_RX_I2C_RST_N;
	writel(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	val = readl(sata_phy->regs + EXYNOS5_SATA_RESET);
	val |= LINK_RESET;
	writel(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	val = readl(sata_phy->regs + EXYNOS5_SATA_RESET);
	val |= RESET_CMN_RST_N;
	writel(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	val = readl(sata_phy->regs + EXYNOS5_SATA_PHSATA_CTRLM);
	val &= ~PHCTRLM_REF_RATE;
	writel(val, sata_phy->regs + EXYNOS5_SATA_PHSATA_CTRLM);

	/* High speed enable for Gen3 */
	val = readl(sata_phy->regs + EXYNOS5_SATA_PHSATA_CTRLM);
	val |= PHCTRLM_HIGH_SPEED;
	writel(val, sata_phy->regs + EXYNOS5_SATA_PHSATA_CTRLM);

	val = readl(sata_phy->regs + EXYNOS5_SATA_CTRL0);
	val |= CTRL0_P0_PHY_CALIBRATED_SEL | CTRL0_P0_PHY_CALIBRATED;
	writel(val, sata_phy->regs + EXYNOS5_SATA_CTRL0);

	val = readl(sata_phy->regs + EXYNOS5_SATA_MODE0);
	val |= SATA_SPD_GEN3;
	writel(val, sata_phy->regs + EXYNOS5_SATA_MODE0);

	ret = i2c_master_send(sata_phy->client, buf, sizeof(buf));
	if (ret < 0)
		return ret;

	/* release cmu reset */
	val = readl(sata_phy->regs + EXYNOS5_SATA_RESET);
	val &= ~RESET_CMN_RST_N;
	writel(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	val = readl(sata_phy->regs + EXYNOS5_SATA_RESET);
	val |= RESET_CMN_RST_N;
	writel(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	ret = wait_for_reg_status(sata_phy->regs,
				EXYNOS5_SATA_PHSATA_STATM,
				PHSTATM_PLL_LOCKED, 1);
	if (ret < 0)
		dev_err(&sata_phy->phy->dev,
			"PHY PLL locking failed\n");
	return ret;
}
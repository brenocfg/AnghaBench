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
typedef  int u32 ;
struct tegra_i2c_dev {int clk_divisor_non_hs_mode; int irq_disabled; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; TYPE_1__* hw; scalar_t__ is_multimaster_mode; scalar_t__ is_dvc; int /*<<< orphan*/  rst; } ;
struct TYPE_2__ {int clk_divisor_hs_mode; scalar_t__ has_slcg_override_reg; scalar_t__ has_mst_fifo; scalar_t__ has_multi_master_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_CLKEN_OVERRIDE ; 
 int /*<<< orphan*/  I2C_CLK_DIVISOR ; 
 int I2C_CLK_DIVISOR_STD_FAST_MODE_SHIFT ; 
 int /*<<< orphan*/  I2C_CNFG ; 
 int I2C_CNFG_DEBOUNCE_CNT_SHIFT ; 
 int I2C_CNFG_MULTI_MASTER_MODE ; 
 int I2C_CNFG_NEW_MASTER_FSM ; 
 int I2C_CNFG_PACKET_MODE_EN ; 
 int /*<<< orphan*/  I2C_FIFO_CONTROL ; 
 int I2C_FIFO_CONTROL_RX_TRIG_SHIFT ; 
 int I2C_FIFO_CONTROL_TX_TRIG_SHIFT ; 
 int /*<<< orphan*/  I2C_INT_MASK ; 
 int I2C_MST_CORE_CLKEN_OVR ; 
 int /*<<< orphan*/  I2C_MST_FIFO_CONTROL ; 
 int I2C_MST_FIFO_CONTROL_RX_TRIG (int) ; 
 int I2C_MST_FIFO_CONTROL_TX_TRIG (int) ; 
 int /*<<< orphan*/  I2C_SL_ADDR1 ; 
 int /*<<< orphan*/  I2C_SL_ADDR2 ; 
 int /*<<< orphan*/  I2C_SL_CNFG ; 
 int I2C_SL_CNFG_NACK ; 
 int I2C_SL_CNFG_NEWSL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int i2c_readl (struct tegra_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_writel (struct tegra_i2c_dev*,int,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dvc_init (struct tegra_i2c_dev*) ; 
 int tegra_i2c_flush_fifos (struct tegra_i2c_dev*) ; 
 int tegra_i2c_wait_for_config_load (struct tegra_i2c_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tegra_i2c_init(struct tegra_i2c_dev *i2c_dev)
{
	u32 val;
	int err;
	u32 clk_divisor;

	err = pm_runtime_get_sync(i2c_dev->dev);
	if (err < 0) {
		dev_err(i2c_dev->dev, "runtime resume failed %d\n", err);
		return err;
	}

	reset_control_assert(i2c_dev->rst);
	udelay(2);
	reset_control_deassert(i2c_dev->rst);

	if (i2c_dev->is_dvc)
		tegra_dvc_init(i2c_dev);

	val = I2C_CNFG_NEW_MASTER_FSM | I2C_CNFG_PACKET_MODE_EN |
		(0x2 << I2C_CNFG_DEBOUNCE_CNT_SHIFT);

	if (i2c_dev->hw->has_multi_master_mode)
		val |= I2C_CNFG_MULTI_MASTER_MODE;

	i2c_writel(i2c_dev, val, I2C_CNFG);
	i2c_writel(i2c_dev, 0, I2C_INT_MASK);

	/* Make sure clock divisor programmed correctly */
	clk_divisor = i2c_dev->hw->clk_divisor_hs_mode;
	clk_divisor |= i2c_dev->clk_divisor_non_hs_mode <<
					I2C_CLK_DIVISOR_STD_FAST_MODE_SHIFT;
	i2c_writel(i2c_dev, clk_divisor, I2C_CLK_DIVISOR);

	if (!i2c_dev->is_dvc) {
		u32 sl_cfg = i2c_readl(i2c_dev, I2C_SL_CNFG);

		sl_cfg |= I2C_SL_CNFG_NACK | I2C_SL_CNFG_NEWSL;
		i2c_writel(i2c_dev, sl_cfg, I2C_SL_CNFG);
		i2c_writel(i2c_dev, 0xfc, I2C_SL_ADDR1);
		i2c_writel(i2c_dev, 0x00, I2C_SL_ADDR2);
	}

	if (i2c_dev->hw->has_mst_fifo) {
		val = I2C_MST_FIFO_CONTROL_TX_TRIG(8) |
		      I2C_MST_FIFO_CONTROL_RX_TRIG(1);
		i2c_writel(i2c_dev, val, I2C_MST_FIFO_CONTROL);
	} else {
		val = 7 << I2C_FIFO_CONTROL_TX_TRIG_SHIFT |
			0 << I2C_FIFO_CONTROL_RX_TRIG_SHIFT;
		i2c_writel(i2c_dev, val, I2C_FIFO_CONTROL);
	}

	err = tegra_i2c_flush_fifos(i2c_dev);
	if (err)
		goto err;

	if (i2c_dev->is_multimaster_mode && i2c_dev->hw->has_slcg_override_reg)
		i2c_writel(i2c_dev, I2C_MST_CORE_CLKEN_OVR, I2C_CLKEN_OVERRIDE);

	err = tegra_i2c_wait_for_config_load(i2c_dev);
	if (err)
		goto err;

	if (i2c_dev->irq_disabled) {
		i2c_dev->irq_disabled = false;
		enable_irq(i2c_dev->irq);
	}

err:
	pm_runtime_put(i2c_dev->dev);
	return err;
}
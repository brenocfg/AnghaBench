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
typedef  int u32 ;
struct nvec_chip {int i2c_addr; int /*<<< orphan*/  irq; scalar_t__ base; int /*<<< orphan*/  i2c_clk; int /*<<< orphan*/  rst; } ;

/* Variables and functions */
 scalar_t__ I2C_CNFG ; 
 int I2C_CNFG_DEBOUNCE_CNT_SHIFT ; 
 int I2C_CNFG_NEW_MASTER_SFM ; 
 int I2C_CNFG_PACKET_MODE_EN ; 
 scalar_t__ I2C_SL_ADDR1 ; 
 scalar_t__ I2C_SL_ADDR2 ; 
 scalar_t__ I2C_SL_CNFG ; 
 scalar_t__ I2C_SL_DELAY_COUNT ; 
 int I2C_SL_NEWSL ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tegra_init_i2c_slave(struct nvec_chip *nvec)
{
	u32 val;

	clk_prepare_enable(nvec->i2c_clk);

	reset_control_assert(nvec->rst);
	udelay(2);
	reset_control_deassert(nvec->rst);

	val = I2C_CNFG_NEW_MASTER_SFM | I2C_CNFG_PACKET_MODE_EN |
	    (0x2 << I2C_CNFG_DEBOUNCE_CNT_SHIFT);
	writel(val, nvec->base + I2C_CNFG);

	clk_set_rate(nvec->i2c_clk, 8 * 80000);

	writel(I2C_SL_NEWSL, nvec->base + I2C_SL_CNFG);
	writel(0x1E, nvec->base + I2C_SL_DELAY_COUNT);

	writel(nvec->i2c_addr >> 1, nvec->base + I2C_SL_ADDR1);
	writel(0, nvec->base + I2C_SL_ADDR2);

	enable_irq(nvec->irq);
}
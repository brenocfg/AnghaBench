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
struct hix5hd2_ir_priv {scalar_t__ base; int /*<<< orphan*/  rate; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int ETIMEDOUT ; 
 scalar_t__ IR_BUSY ; 
 int IR_CFG_FORMAT_MASK ; 
 int IR_CFG_FORMAT_SHIFT ; 
 int IR_CFG_FREQ_MASK ; 
 int IR_CFG_FREQ_SHIFT ; 
 int IR_CFG_INT_LEVEL_MASK ; 
 int IR_CFG_INT_LEVEL_SHIFT ; 
 int IR_CFG_INT_THRESHOLD ; 
 int IR_CFG_MODE_RAW ; 
 int IR_CFG_SYMBOL_FMT ; 
 int IR_CFG_SYMBOL_MAXWIDTH ; 
 int IR_CFG_WIDTH_MASK ; 
 int IR_CFG_WIDTH_SHIFT ; 
 scalar_t__ IR_CONFIG ; 
 scalar_t__ IR_ENABLE ; 
 scalar_t__ IR_INTM ; 
 scalar_t__ IR_START ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int hix5hd2_ir_config(struct hix5hd2_ir_priv *priv)
{
	int timeout = 10000;
	u32 val, rate;

	writel_relaxed(0x01, priv->base + IR_ENABLE);
	while (readl_relaxed(priv->base + IR_BUSY)) {
		if (timeout--) {
			udelay(1);
		} else {
			dev_err(priv->dev, "IR_BUSY timeout\n");
			return -ETIMEDOUT;
		}
	}

	/* Now only support raw mode, with symbol start from low to high */
	rate = DIV_ROUND_CLOSEST(priv->rate, 1000000);
	val = IR_CFG_SYMBOL_MAXWIDTH & IR_CFG_WIDTH_MASK << IR_CFG_WIDTH_SHIFT;
	val |= IR_CFG_SYMBOL_FMT & IR_CFG_FORMAT_MASK << IR_CFG_FORMAT_SHIFT;
	val |= (IR_CFG_INT_THRESHOLD - 1) & IR_CFG_INT_LEVEL_MASK
	       << IR_CFG_INT_LEVEL_SHIFT;
	val |= IR_CFG_MODE_RAW;
	val |= (rate - 1) & IR_CFG_FREQ_MASK << IR_CFG_FREQ_SHIFT;
	writel_relaxed(val, priv->base + IR_CONFIG);

	writel_relaxed(0x00, priv->base + IR_INTM);
	/* write arbitrary value to start  */
	writel_relaxed(0x01, priv->base + IR_START);
	return 0;
}
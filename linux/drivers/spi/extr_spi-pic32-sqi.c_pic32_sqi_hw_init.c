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
typedef  unsigned int u32 ;
struct pic32_sqi {int cur_mode; scalar_t__ cur_speed; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ PESQI_BD_POLL_CTRL_REG ; 
 unsigned int PESQI_BURST_EN ; 
 scalar_t__ PESQI_CMD_THRES_REG ; 
 scalar_t__ PESQI_CONF_REG ; 
 unsigned int PESQI_CSEN_SHIFT ; 
 scalar_t__ PESQI_INT_THRES_REG ; 
 unsigned int PESQI_LANES_SHIFT ; 
 unsigned int PESQI_MODE ; 
 unsigned int PESQI_MODE_DMA ; 
 unsigned int PESQI_MODE_SHIFT ; 
 unsigned int PESQI_QUAD_LANE ; 
 unsigned int PESQI_RXTHR_MASK ; 
 unsigned int PESQI_RXTHR_SHIFT ; 
 unsigned int PESQI_SOFT_RESET ; 
 unsigned int PESQI_TXTHR_MASK ; 
 unsigned int PESQI_TXTHR_SHIFT ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pic32_sqi_disable_int (struct pic32_sqi*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  readl_poll_timeout_atomic (scalar_t__,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void pic32_sqi_hw_init(struct pic32_sqi *sqi)
{
	unsigned long flags;
	u32 val;

	/* Soft-reset of PESQI controller triggers interrupt.
	 * We are not yet ready to handle them so disable CPU
	 * interrupt for the time being.
	 */
	local_irq_save(flags);

	/* assert soft-reset */
	writel(PESQI_SOFT_RESET, sqi->regs + PESQI_CONF_REG);

	/* wait until clear */
	readl_poll_timeout_atomic(sqi->regs + PESQI_CONF_REG, val,
				  !(val & PESQI_SOFT_RESET), 1, 5000);

	/* disable all interrupts */
	pic32_sqi_disable_int(sqi);

	/* Now it is safe to enable back CPU interrupt */
	local_irq_restore(flags);

	/* tx and rx fifo interrupt threshold */
	val = readl(sqi->regs + PESQI_CMD_THRES_REG);
	val &= ~(PESQI_TXTHR_MASK << PESQI_TXTHR_SHIFT);
	val &= ~(PESQI_RXTHR_MASK << PESQI_RXTHR_SHIFT);
	val |= (1U << PESQI_TXTHR_SHIFT) | (1U << PESQI_RXTHR_SHIFT);
	writel(val, sqi->regs + PESQI_CMD_THRES_REG);

	val = readl(sqi->regs + PESQI_INT_THRES_REG);
	val &= ~(PESQI_TXTHR_MASK << PESQI_TXTHR_SHIFT);
	val &= ~(PESQI_RXTHR_MASK << PESQI_RXTHR_SHIFT);
	val |= (1U << PESQI_TXTHR_SHIFT) | (1U << PESQI_RXTHR_SHIFT);
	writel(val, sqi->regs + PESQI_INT_THRES_REG);

	/* default configuration */
	val = readl(sqi->regs + PESQI_CONF_REG);

	/* set mode: DMA */
	val &= ~PESQI_MODE;
	val |= PESQI_MODE_DMA << PESQI_MODE_SHIFT;
	writel(val, sqi->regs + PESQI_CONF_REG);

	/* DATAEN - SQIID0-ID3 */
	val |= PESQI_QUAD_LANE << PESQI_LANES_SHIFT;

	/* burst/INCR4 enable */
	val |= PESQI_BURST_EN;

	/* CSEN - all CS */
	val |= 3U << PESQI_CSEN_SHIFT;
	writel(val, sqi->regs + PESQI_CONF_REG);

	/* write poll count */
	writel(0, sqi->regs + PESQI_BD_POLL_CTRL_REG);

	sqi->cur_speed = 0;
	sqi->cur_mode = -1;
}
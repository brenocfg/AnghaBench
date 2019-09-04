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
struct stm32_timers_dma {int /*<<< orphan*/  lock; int /*<<< orphan*/ * chan; int /*<<< orphan*/  completion; scalar_t__ phys_base; int /*<<< orphan*/ ** chans; } ;
struct stm32_timers {struct stm32_timers_dma dma; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct dma_slave_config {int /*<<< orphan*/  src_addr_width; scalar_t__ src_addr; } ;
struct dma_async_tx_descriptor {struct stm32_timers_dma* callback_param; int /*<<< orphan*/  callback; } ;
struct device {int dummy; } ;
typedef  enum stm32_timers_dmas { ____Placeholder_stm32_timers_dmas } stm32_timers_dmas ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
typedef  scalar_t__ dma_addr_t ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 unsigned int FIELD_PREP (int /*<<< orphan*/ ,unsigned int) ; 
 int STM32_TIMERS_DMA_CH1 ; 
 int STM32_TIMERS_MAX_DMAS ; 
 unsigned int STM32_TIMERS_MAX_REGISTERS ; 
 int /*<<< orphan*/  TIM_DCR ; 
 int /*<<< orphan*/  TIM_DCR_DBA ; 
 int /*<<< orphan*/  TIM_DCR_DBL ; 
 int /*<<< orphan*/  TIM_DIER ; 
 scalar_t__ TIM_DMAR ; 
 int /*<<< orphan*/  TIM_SR ; 
 struct stm32_timers* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ dma_map_single (struct device*,unsigned int*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,scalar_t__) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_single (int /*<<< orphan*/ *,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ *,struct dma_slave_config*) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dma_slave_config*,int /*<<< orphan*/ ,int) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stm32_timers_dier_dmaen ; 
 int /*<<< orphan*/  stm32_timers_dma_done ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,unsigned long) ; 

int stm32_timers_dma_burst_read(struct device *dev, u32 *buf,
				enum stm32_timers_dmas id, u32 reg,
				unsigned int num_reg, unsigned int bursts,
				unsigned long tmo_ms)
{
	struct stm32_timers *ddata = dev_get_drvdata(dev);
	unsigned long timeout = msecs_to_jiffies(tmo_ms);
	struct regmap *regmap = ddata->regmap;
	struct stm32_timers_dma *dma = &ddata->dma;
	size_t len = num_reg * bursts * sizeof(u32);
	struct dma_async_tx_descriptor *desc;
	struct dma_slave_config config;
	dma_cookie_t cookie;
	dma_addr_t dma_buf;
	u32 dbl, dba;
	long err;
	int ret;

	/* Sanity check */
	if (id < STM32_TIMERS_DMA_CH1 || id >= STM32_TIMERS_MAX_DMAS)
		return -EINVAL;

	if (!num_reg || !bursts || reg > STM32_TIMERS_MAX_REGISTERS ||
	    (reg + num_reg * sizeof(u32)) > STM32_TIMERS_MAX_REGISTERS)
		return -EINVAL;

	if (!dma->chans[id])
		return -ENODEV;
	mutex_lock(&dma->lock);

	/* Select DMA channel in use */
	dma->chan = dma->chans[id];
	dma_buf = dma_map_single(dev, buf, len, DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, dma_buf)) {
		ret = -ENOMEM;
		goto unlock;
	}

	/* Prepare DMA read from timer registers, using DMA burst mode */
	memset(&config, 0, sizeof(config));
	config.src_addr = (dma_addr_t)dma->phys_base + TIM_DMAR;
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	ret = dmaengine_slave_config(dma->chan, &config);
	if (ret)
		goto unmap;

	desc = dmaengine_prep_slave_single(dma->chan, dma_buf, len,
					   DMA_DEV_TO_MEM, DMA_PREP_INTERRUPT);
	if (!desc) {
		ret = -EBUSY;
		goto unmap;
	}

	desc->callback = stm32_timers_dma_done;
	desc->callback_param = dma;
	cookie = dmaengine_submit(desc);
	ret = dma_submit_error(cookie);
	if (ret)
		goto dma_term;

	reinit_completion(&dma->completion);
	dma_async_issue_pending(dma->chan);

	/* Setup and enable timer DMA burst mode */
	dbl = FIELD_PREP(TIM_DCR_DBL, bursts - 1);
	dba = FIELD_PREP(TIM_DCR_DBA, reg >> 2);
	ret = regmap_write(regmap, TIM_DCR, dbl | dba);
	if (ret)
		goto dma_term;

	/* Clear pending flags before enabling DMA request */
	ret = regmap_write(regmap, TIM_SR, 0);
	if (ret)
		goto dcr_clr;

	ret = regmap_update_bits(regmap, TIM_DIER, stm32_timers_dier_dmaen[id],
				 stm32_timers_dier_dmaen[id]);
	if (ret)
		goto dcr_clr;

	err = wait_for_completion_interruptible_timeout(&dma->completion,
							timeout);
	if (err == 0)
		ret = -ETIMEDOUT;
	else if (err < 0)
		ret = err;

	regmap_update_bits(regmap, TIM_DIER, stm32_timers_dier_dmaen[id], 0);
	regmap_write(regmap, TIM_SR, 0);
dcr_clr:
	regmap_write(regmap, TIM_DCR, 0);
dma_term:
	dmaengine_terminate_all(dma->chan);
unmap:
	dma_unmap_single(dev, dma_buf, len, DMA_FROM_DEVICE);
unlock:
	dma->chan = NULL;
	mutex_unlock(&dma->lock);

	return ret;
}
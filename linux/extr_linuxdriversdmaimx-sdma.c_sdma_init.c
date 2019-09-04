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
struct sdma_engine {int context_phys; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/ * channel; scalar_t__ regs; TYPE_1__* drvdata; scalar_t__ channel_control; void* context; } ;
struct sdma_context_data {int dummy; } ;
struct sdma_channel_control {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int num_events; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_DMA_CHANNELS ; 
 scalar_t__ SDMA_CHN0ADDR ; 
 scalar_t__ SDMA_CHNPRI_0 ; 
 scalar_t__ SDMA_H_C0PTR ; 
 scalar_t__ SDMA_H_CONFIG ; 
 scalar_t__ chnenbl_ofs (struct sdma_engine*,int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdma_config_ownership (int /*<<< orphan*/ *,int,int,int) ; 
 int sdma_request_channel0 (struct sdma_engine*) ; 
 int /*<<< orphan*/  sdma_set_channel_priority (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int sdma_init(struct sdma_engine *sdma)
{
	int i, ret;
	dma_addr_t ccb_phys;

	ret = clk_enable(sdma->clk_ipg);
	if (ret)
		return ret;
	ret = clk_enable(sdma->clk_ahb);
	if (ret)
		goto disable_clk_ipg;

	/* Be sure SDMA has not started yet */
	writel_relaxed(0, sdma->regs + SDMA_H_C0PTR);

	sdma->channel_control = dma_alloc_coherent(NULL,
			MAX_DMA_CHANNELS * sizeof (struct sdma_channel_control) +
			sizeof(struct sdma_context_data),
			&ccb_phys, GFP_KERNEL);

	if (!sdma->channel_control) {
		ret = -ENOMEM;
		goto err_dma_alloc;
	}

	sdma->context = (void *)sdma->channel_control +
		MAX_DMA_CHANNELS * sizeof (struct sdma_channel_control);
	sdma->context_phys = ccb_phys +
		MAX_DMA_CHANNELS * sizeof (struct sdma_channel_control);

	/* Zero-out the CCB structures array just allocated */
	memset(sdma->channel_control, 0,
			MAX_DMA_CHANNELS * sizeof (struct sdma_channel_control));

	/* disable all channels */
	for (i = 0; i < sdma->drvdata->num_events; i++)
		writel_relaxed(0, sdma->regs + chnenbl_ofs(sdma, i));

	/* All channels have priority 0 */
	for (i = 0; i < MAX_DMA_CHANNELS; i++)
		writel_relaxed(0, sdma->regs + SDMA_CHNPRI_0 + i * 4);

	ret = sdma_request_channel0(sdma);
	if (ret)
		goto err_dma_alloc;

	sdma_config_ownership(&sdma->channel[0], false, true, false);

	/* Set Command Channel (Channel Zero) */
	writel_relaxed(0x4050, sdma->regs + SDMA_CHN0ADDR);

	/* Set bits of CONFIG register but with static context switching */
	/* FIXME: Check whether to set ACR bit depending on clock ratios */
	writel_relaxed(0, sdma->regs + SDMA_H_CONFIG);

	writel_relaxed(ccb_phys, sdma->regs + SDMA_H_C0PTR);

	/* Initializes channel's priorities */
	sdma_set_channel_priority(&sdma->channel[0], 7);

	clk_disable(sdma->clk_ipg);
	clk_disable(sdma->clk_ahb);

	return 0;

err_dma_alloc:
	clk_disable(sdma->clk_ahb);
disable_clk_ipg:
	clk_disable(sdma->clk_ipg);
	dev_err(sdma->dev, "initialisation failed with %d\n", ret);
	return ret;
}
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
struct hidma_lldev {scalar_t__ evca; void* evch_state; void* trch_state; int /*<<< orphan*/  dev; scalar_t__ trca; } ;

/* Variables and functions */
 int ENABLE_IRQS ; 
 int HIDMA_CH_CONTROL_MASK ; 
 int HIDMA_CH_ENABLE ; 
 void* HIDMA_CH_ENABLED ; 
 int /*<<< orphan*/  HIDMA_CH_STATE (int) ; 
 scalar_t__ HIDMA_EVCA_CTRLSTS_REG ; 
 scalar_t__ HIDMA_EVCA_IRQ_EN_REG ; 
 scalar_t__ HIDMA_TRCA_CTRLSTS_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hidma_is_chan_enabled (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int hidma_ll_enable(struct hidma_lldev *lldev)
{
	u32 val;
	int ret;

	val = readl(lldev->evca + HIDMA_EVCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_ENABLE << 16;
	writel(val, lldev->evca + HIDMA_EVCA_CTRLSTS_REG);

	ret = readl_poll_timeout(lldev->evca + HIDMA_EVCA_CTRLSTS_REG, val,
				 hidma_is_chan_enabled(HIDMA_CH_STATE(val)),
				 1000, 10000);
	if (ret) {
		dev_err(lldev->dev, "event channel did not get enabled\n");
		return ret;
	}

	val = readl(lldev->trca + HIDMA_TRCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_ENABLE << 16;
	writel(val, lldev->trca + HIDMA_TRCA_CTRLSTS_REG);

	ret = readl_poll_timeout(lldev->trca + HIDMA_TRCA_CTRLSTS_REG, val,
				 hidma_is_chan_enabled(HIDMA_CH_STATE(val)),
				 1000, 10000);
	if (ret) {
		dev_err(lldev->dev, "transfer channel did not get enabled\n");
		return ret;
	}

	lldev->trch_state = HIDMA_CH_ENABLED;
	lldev->evch_state = HIDMA_CH_ENABLED;

	/* enable irqs */
	writel(ENABLE_IRQS, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);

	return 0;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct sunxi_rtc_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SUNXI_ALRM_EN ; 
 int /*<<< orphan*/  SUNXI_ALRM_EN_CNT_EN ; 
 scalar_t__ SUNXI_ALRM_IRQ_EN ; 
 int /*<<< orphan*/  SUNXI_ALRM_IRQ_EN_CNT_IRQ_EN ; 
 scalar_t__ SUNXI_ALRM_IRQ_STA ; 
 int /*<<< orphan*/  SUNXI_ALRM_IRQ_STA_CNT_IRQ_PEND ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sunxi_rtc_setaie(unsigned int to, struct sunxi_rtc_dev *chip)
{
	u32 alrm_val = 0;
	u32 alrm_irq_val = 0;

	if (to) {
		alrm_val = readl(chip->base + SUNXI_ALRM_EN);
		alrm_val |= SUNXI_ALRM_EN_CNT_EN;

		alrm_irq_val = readl(chip->base + SUNXI_ALRM_IRQ_EN);
		alrm_irq_val |= SUNXI_ALRM_IRQ_EN_CNT_IRQ_EN;
	} else {
		writel(SUNXI_ALRM_IRQ_STA_CNT_IRQ_PEND,
				chip->base + SUNXI_ALRM_IRQ_STA);
	}

	writel(alrm_val, chip->base + SUNXI_ALRM_EN);
	writel(alrm_irq_val, chip->base + SUNXI_ALRM_IRQ_EN);
}
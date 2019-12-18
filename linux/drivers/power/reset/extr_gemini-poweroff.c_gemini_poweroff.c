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
struct gemini_powercon {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GEMINI_CTRL_ENABLE ; 
 int GEMINI_CTRL_IRQ_CLR ; 
 int GEMINI_CTRL_SHUTDOWN ; 
 scalar_t__ GEMINI_PWC_CTRLREG ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 struct gemini_powercon* gpw_poweroff ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gemini_poweroff(void)
{
	struct gemini_powercon *gpw = gpw_poweroff;
	u32 val;

	dev_crit(gpw->dev, "Gemini power off\n");
	val = readl(gpw->base + GEMINI_PWC_CTRLREG);
	val |= GEMINI_CTRL_ENABLE | GEMINI_CTRL_IRQ_CLR;
	writel(val, gpw->base + GEMINI_PWC_CTRLREG);

	val &= ~GEMINI_CTRL_ENABLE;
	val |= GEMINI_CTRL_SHUTDOWN;
	writel(val, gpw->base + GEMINI_PWC_CTRLREG);
}
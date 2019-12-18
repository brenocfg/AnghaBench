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
typedef  int uint32_t ;
struct pxafb_info {int lccr0; int /*<<< orphan*/  clk; int /*<<< orphan*/  disable_done; int /*<<< orphan*/  refresh_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCCR0 ; 
 int LCCR0_DIS ; 
 int LCCR0_LCDT ; 
 int LCCR0_LDM ; 
 int /*<<< orphan*/  LCSR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int lcd_readl (struct pxafb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_writel (struct pxafb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxafb_disable_controller(struct pxafb_info *fbi)
{
	uint32_t lccr0;

#ifdef CONFIG_FB_PXA_SMARTPANEL
	if (fbi->lccr0 & LCCR0_LCDT) {
		wait_for_completion_timeout(&fbi->refresh_done,
				msecs_to_jiffies(200));
		return;
	}
#endif

	/* Clear LCD Status Register */
	lcd_writel(fbi, LCSR, 0xffffffff);

	lccr0 = lcd_readl(fbi, LCCR0) & ~LCCR0_LDM;
	lcd_writel(fbi, LCCR0, lccr0);
	lcd_writel(fbi, LCCR0, lccr0 | LCCR0_DIS);

	wait_for_completion_timeout(&fbi->disable_done, msecs_to_jiffies(200));

	/* disable LCD controller clock */
	clk_disable_unprepare(fbi->clk);
}
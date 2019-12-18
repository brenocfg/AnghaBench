#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct clcd_fb {int clk_enabled; int /*<<< orphan*/  clk; scalar_t__ off_cntl; scalar_t__ regs; TYPE_3__* panel; TYPE_1__* board; } ;
struct TYPE_6__ {int /*<<< orphan*/  power; } ;
struct TYPE_8__ {TYPE_2__ props; } ;
struct TYPE_7__ {TYPE_4__* backlight; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* disable ) (struct clcd_fb*) ;} ;

/* Variables and functions */
 int CNTL_LCDEN ; 
 int CNTL_LCDPWR ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  backlight_update_status (TYPE_4__*) ; 
 int /*<<< orphan*/  clcdfb_sleep (int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct clcd_fb*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void clcdfb_disable(struct clcd_fb *fb)
{
	u32 val;

	if (fb->board->disable)
		fb->board->disable(fb);

	if (fb->panel->backlight) {
		fb->panel->backlight->props.power = FB_BLANK_POWERDOWN;
		backlight_update_status(fb->panel->backlight);
	}

	val = readl(fb->regs + fb->off_cntl);
	if (val & CNTL_LCDPWR) {
		val &= ~CNTL_LCDPWR;
		writel(val, fb->regs + fb->off_cntl);

		clcdfb_sleep(20);
	}
	if (val & CNTL_LCDEN) {
		val &= ~CNTL_LCDEN;
		writel(val, fb->regs + fb->off_cntl);
	}

	/*
	 * Disable CLCD clock source.
	 */
	if (fb->clk_enabled) {
		fb->clk_enabled = false;
		clk_disable(fb->clk);
	}
}
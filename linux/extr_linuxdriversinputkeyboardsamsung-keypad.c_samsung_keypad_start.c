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
struct samsung_keypad {int stopped; TYPE_1__* pdev; scalar_t__ base; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SAMSUNG_KEYIFCOL ; 
 scalar_t__ SAMSUNG_KEYIFCON ; 
 unsigned int SAMSUNG_KEYIFCON_INT_F_EN ; 
 unsigned int SAMSUNG_KEYIFCON_INT_R_EN ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void samsung_keypad_start(struct samsung_keypad *keypad)
{
	unsigned int val;

	pm_runtime_get_sync(&keypad->pdev->dev);

	/* Tell IRQ thread that it may poll the device. */
	keypad->stopped = false;

	clk_enable(keypad->clk);

	/* Enable interrupt bits. */
	val = readl(keypad->base + SAMSUNG_KEYIFCON);
	val |= SAMSUNG_KEYIFCON_INT_F_EN | SAMSUNG_KEYIFCON_INT_R_EN;
	writel(val, keypad->base + SAMSUNG_KEYIFCON);

	/* KEYIFCOL reg clear. */
	writel(0, keypad->base + SAMSUNG_KEYIFCOL);

	pm_runtime_put(&keypad->pdev->dev);
}
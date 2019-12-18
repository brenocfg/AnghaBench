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
struct samsung_keypad {int stopped; TYPE_1__* pdev; int /*<<< orphan*/  irq; int /*<<< orphan*/  clk; scalar_t__ base; int /*<<< orphan*/  wait; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SAMSUNG_KEYIFCON ; 
 unsigned int SAMSUNG_KEYIFCON_INT_F_EN ; 
 unsigned int SAMSUNG_KEYIFCON_INT_R_EN ; 
 scalar_t__ SAMSUNG_KEYIFSTSCLR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void samsung_keypad_stop(struct samsung_keypad *keypad)
{
	unsigned int val;

	pm_runtime_get_sync(&keypad->pdev->dev);

	/* Signal IRQ thread to stop polling and disable the handler. */
	keypad->stopped = true;
	wake_up(&keypad->wait);
	disable_irq(keypad->irq);

	/* Clear interrupt. */
	writel(~0x0, keypad->base + SAMSUNG_KEYIFSTSCLR);

	/* Disable interrupt bits. */
	val = readl(keypad->base + SAMSUNG_KEYIFCON);
	val &= ~(SAMSUNG_KEYIFCON_INT_F_EN | SAMSUNG_KEYIFCON_INT_R_EN);
	writel(val, keypad->base + SAMSUNG_KEYIFCON);

	clk_disable(keypad->clk);

	/*
	 * Now that chip should not generate interrupts we can safely
	 * re-enable the handler.
	 */
	enable_irq(keypad->irq);

	pm_runtime_put(&keypad->pdev->dev);
}
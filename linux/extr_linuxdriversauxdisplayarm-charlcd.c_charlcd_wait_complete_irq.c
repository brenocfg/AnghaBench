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
struct charlcd {int /*<<< orphan*/  dev; scalar_t__ virtbase; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHARLCD_TIMEOUT ; 
 scalar_t__ CHAR_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void charlcd_wait_complete_irq(struct charlcd *lcd)
{
	int ret;

	ret = wait_for_completion_interruptible_timeout(&lcd->complete,
							CHARLCD_TIMEOUT);
	/* Disable IRQ after completion */
	writel(0x00, lcd->virtbase + CHAR_MASK);

	if (ret < 0) {
		dev_err(lcd->dev,
			"wait_for_completion_interruptible_timeout() "
			"returned %d waiting for ready\n", ret);
		return;
	}

	if (ret == 0) {
		dev_err(lcd->dev, "charlcd controller timed out "
			"waiting for ready\n");
		return;
	}
}
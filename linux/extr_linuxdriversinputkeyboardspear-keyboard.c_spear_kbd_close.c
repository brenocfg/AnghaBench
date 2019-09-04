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
struct spear_kbd {int /*<<< orphan*/  last_key; int /*<<< orphan*/  clk; scalar_t__ io_base; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_RESERVED ; 
 scalar_t__ MODE_CTL_REG ; 
 int /*<<< orphan*/  MODE_CTL_START_SCAN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct spear_kbd* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void spear_kbd_close(struct input_dev *dev)
{
	struct spear_kbd *kbd = input_get_drvdata(dev);
	u32 val;

	/* stop key scan */
	val = readl_relaxed(kbd->io_base + MODE_CTL_REG);
	val &= ~MODE_CTL_START_SCAN;
	writel_relaxed(val, kbd->io_base + MODE_CTL_REG);

	clk_disable(kbd->clk);

	kbd->last_key = KEY_RESERVED;
}
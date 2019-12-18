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
struct spear_kbd {int mode; scalar_t__ io_base; int /*<<< orphan*/  clk; int /*<<< orphan*/  last_key; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_RESERVED ; 
 int MODE_CTL_KEYBOARD ; 
 int MODE_CTL_KEYNUM_SHIFT ; 
 int MODE_CTL_PCLK_FREQ_MSK ; 
 int MODE_CTL_PCLK_FREQ_SHIFT ; 
 scalar_t__ MODE_CTL_REG ; 
 int MODE_CTL_SCAN_RATE_80 ; 
 int MODE_CTL_START_SCAN ; 
 scalar_t__ STATUS_REG ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct spear_kbd* input_get_drvdata (struct input_dev*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int spear_kbd_open(struct input_dev *dev)
{
	struct spear_kbd *kbd = input_get_drvdata(dev);
	int error;
	u32 val;

	kbd->last_key = KEY_RESERVED;

	error = clk_enable(kbd->clk);
	if (error)
		return error;

	/* keyboard rate to be programmed is input clock (in MHz) - 1 */
	val = clk_get_rate(kbd->clk) / 1000000 - 1;
	val = (val & MODE_CTL_PCLK_FREQ_MSK) << MODE_CTL_PCLK_FREQ_SHIFT;

	/* program keyboard */
	val = MODE_CTL_SCAN_RATE_80 | MODE_CTL_KEYBOARD | val |
		(kbd->mode << MODE_CTL_KEYNUM_SHIFT);
	writel_relaxed(val, kbd->io_base + MODE_CTL_REG);
	writel_relaxed(1, kbd->io_base + STATUS_REG);

	/* start key scan */
	val = readl_relaxed(kbd->io_base + MODE_CTL_REG);
	val |= MODE_CTL_START_SCAN;
	writel_relaxed(val, kbd->io_base + MODE_CTL_REG);

	return 0;
}
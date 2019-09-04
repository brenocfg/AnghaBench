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
struct w90p910_keypad_platform_data {unsigned int prescale; unsigned int debounce; } ;
struct w90p910_keypad {scalar_t__ mmio_base; int /*<<< orphan*/  clk; struct w90p910_keypad_platform_data* pdata; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 unsigned int DEBOUNCE_BIT ; 
 unsigned int ENKP ; 
 scalar_t__ KPI_CONF ; 
 unsigned int KPSEL ; 
 unsigned int KSIZE0 ; 
 unsigned int KSIZE1 ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct w90p910_keypad* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int w90p910_keypad_open(struct input_dev *dev)
{
	struct w90p910_keypad *keypad = input_get_drvdata(dev);
	const struct w90p910_keypad_platform_data *pdata = keypad->pdata;
	unsigned int val, config;

	/* Enable unit clock */
	clk_enable(keypad->clk);

	val = __raw_readl(keypad->mmio_base + KPI_CONF);
	val |= (KPSEL | ENKP);
	val &= ~(KSIZE0 | KSIZE1);

	config = pdata->prescale | (pdata->debounce << DEBOUNCE_BIT);

	val |= config;

	__raw_writel(val, keypad->mmio_base + KPI_CONF);

	return 0;
}
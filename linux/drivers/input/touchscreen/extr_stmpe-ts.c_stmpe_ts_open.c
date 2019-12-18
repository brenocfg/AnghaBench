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
struct stmpe_touch {int /*<<< orphan*/  stmpe; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMPE_REG_TSC_CTRL ; 
 int /*<<< orphan*/  STMPE_TSC_CTRL_TSC_EN ; 
 int __stmpe_reset_fifo (int /*<<< orphan*/ ) ; 
 struct stmpe_touch* input_get_drvdata (struct input_dev*) ; 
 int stmpe_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmpe_ts_open(struct input_dev *dev)
{
	struct stmpe_touch *ts = input_get_drvdata(dev);
	int ret = 0;

	ret = __stmpe_reset_fifo(ts->stmpe);
	if (ret)
		return ret;

	return stmpe_set_bits(ts->stmpe, STMPE_REG_TSC_CTRL,
			STMPE_TSC_CTRL_TSC_EN, STMPE_TSC_CTRL_TSC_EN);
}
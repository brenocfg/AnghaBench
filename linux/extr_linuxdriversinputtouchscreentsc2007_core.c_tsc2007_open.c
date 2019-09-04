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
struct tsc2007 {int stopped; int /*<<< orphan*/  irq; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWRDOWN ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct tsc2007* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  tsc2007_stop (struct tsc2007*) ; 
 int tsc2007_xfer (struct tsc2007*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsc2007_open(struct input_dev *input_dev)
{
	struct tsc2007 *ts = input_get_drvdata(input_dev);
	int err;

	ts->stopped = false;
	mb();

	enable_irq(ts->irq);

	/* Prepare for touch readings - power down ADC and enable PENIRQ */
	err = tsc2007_xfer(ts, PWRDOWN);
	if (err < 0) {
		tsc2007_stop(ts);
		return err;
	}

	return 0;
}
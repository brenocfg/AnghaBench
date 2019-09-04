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
struct mxs_lradc_ts {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct mxs_lradc_ts* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mxs_lradc_enable_touch_detection (struct mxs_lradc_ts*) ; 

__attribute__((used)) static int mxs_lradc_ts_open(struct input_dev *dev)
{
	struct mxs_lradc_ts *ts = input_get_drvdata(dev);

	/* Enable the touch-detect circuitry. */
	mxs_lradc_enable_touch_detection(ts);

	return 0;
}
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
struct sun4i_ts_data {scalar_t__ base; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEMP_IRQ_EN (int) ; 
 scalar_t__ TP_INT_FIFOC ; 
 struct sun4i_ts_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sun4i_ts_close(struct input_dev *dev)
{
	struct sun4i_ts_data *ts = input_get_drvdata(dev);

	/* Deactivate all input IRQs */
	writel(TEMP_IRQ_EN(1), ts->base + TP_INT_FIFOC);
}
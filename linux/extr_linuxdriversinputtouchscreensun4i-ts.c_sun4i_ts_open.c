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
 int DATA_IRQ_EN (int) ; 
 int FIFO_FLUSH (int) ; 
 int FIFO_TRIG (int) ; 
 int TEMP_IRQ_EN (int) ; 
 scalar_t__ TP_INT_FIFOC ; 
 int TP_UP_IRQ_EN (int) ; 
 struct sun4i_ts_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sun4i_ts_open(struct input_dev *dev)
{
	struct sun4i_ts_data *ts = input_get_drvdata(dev);

	/* Flush, set trig level to 1, enable temp, data and up irqs */
	writel(TEMP_IRQ_EN(1) | DATA_IRQ_EN(1) | FIFO_TRIG(1) | FIFO_FLUSH(1) |
		TP_UP_IRQ_EN(1), ts->base + TP_INT_FIFOC);

	return 0;
}
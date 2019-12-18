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
struct sun4i_ts_data {scalar_t__ base; scalar_t__ input; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TP_INT_FIFOC ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 struct sun4i_ts_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sun4i_ts_remove(struct platform_device *pdev)
{
	struct sun4i_ts_data *ts = platform_get_drvdata(pdev);

	/* Explicit unregister to avoid open/close changing the imask later */
	if (ts->input)
		input_unregister_device(ts->input);

	/* Deactivate all IRQs */
	writel(0, ts->base + TP_INT_FIFOC);

	return 0;
}
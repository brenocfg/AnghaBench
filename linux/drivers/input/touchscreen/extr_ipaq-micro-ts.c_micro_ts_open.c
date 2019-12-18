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
struct touchscreen_data {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct touchscreen_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  micro_ts_toggle_receive (struct touchscreen_data*,int) ; 

__attribute__((used)) static int micro_ts_open(struct input_dev *input)
{
	struct touchscreen_data *ts = input_get_drvdata(input);

	micro_ts_toggle_receive(ts, true);

	return 0;
}
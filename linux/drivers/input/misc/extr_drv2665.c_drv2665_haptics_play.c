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
struct input_dev {int dummy; } ;
struct ff_effect {int dummy; } ;
struct drv2665_data {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 struct drv2665_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drv2665_haptics_play(struct input_dev *input, void *data,
				struct ff_effect *effect)
{
	struct drv2665_data *haptics = input_get_drvdata(input);

	schedule_work(&haptics->work);

	return 0;
}
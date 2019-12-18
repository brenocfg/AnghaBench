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
struct mxt_data {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct mxt_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mxt_start (struct mxt_data*) ; 

__attribute__((used)) static int mxt_input_open(struct input_dev *dev)
{
	struct mxt_data *data = input_get_drvdata(dev);

	mxt_start(data);

	return 0;
}
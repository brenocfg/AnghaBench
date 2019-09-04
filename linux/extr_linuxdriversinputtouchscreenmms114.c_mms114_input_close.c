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
struct mms114_data {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct mms114_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mms114_stop (struct mms114_data*) ; 

__attribute__((used)) static void mms114_input_close(struct input_dev *dev)
{
	struct mms114_data *data = input_get_drvdata(dev);

	mms114_stop(data);
}
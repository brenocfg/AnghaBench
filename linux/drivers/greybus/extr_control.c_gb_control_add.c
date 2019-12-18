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
struct gb_control {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_add (int /*<<< orphan*/ *) ; 

int gb_control_add(struct gb_control *control)
{
	int ret;

	ret = device_add(&control->dev);
	if (ret) {
		dev_err(&control->dev,
			"failed to register control device: %d\n",
			ret);
		return ret;
	}

	return 0;
}
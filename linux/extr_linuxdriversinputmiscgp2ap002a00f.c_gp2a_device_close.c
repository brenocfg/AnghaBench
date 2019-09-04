#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct input_dev {int dummy; } ;
struct gp2a_data {TYPE_1__* i2c_client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gp2a_disable (struct gp2a_data*) ; 
 struct gp2a_data* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void gp2a_device_close(struct input_dev *dev)
{
	struct gp2a_data *dt = input_get_drvdata(dev);
	int error;

	error = gp2a_disable(dt);
	if (error < 0)
		dev_err(&dt->i2c_client->dev,
			"unable to deactivate, err %d\n", error);
}
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
struct device {int dummy; } ;
struct rmi_function {struct device dev; } ;
struct f03_data {int device_count; struct rmi_function* fn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct f03_data*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct f03_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int rmi_f03_initialize (struct f03_data*) ; 

__attribute__((used)) static int rmi_f03_probe(struct rmi_function *fn)
{
	struct device *dev = &fn->dev;
	struct f03_data *f03;
	int error;

	f03 = devm_kzalloc(dev, sizeof(struct f03_data), GFP_KERNEL);
	if (!f03)
		return -ENOMEM;

	f03->fn = fn;

	error = rmi_f03_initialize(f03);
	if (error < 0)
		return error;

	if (f03->device_count != 1)
		dev_warn(dev, "found %d devices on PS/2 passthrough",
			 f03->device_count);

	dev_set_drvdata(dev, f03);
	return 0;
}
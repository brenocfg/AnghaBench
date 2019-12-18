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
struct rmi_driver_data {int /*<<< orphan*/  f01_container; } ;
struct rmi_device {int /*<<< orphan*/  dev; } ;
struct input_dev {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rmi_driver_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 char* devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 char* rmi_f01_get_product_ID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rmi_driver_set_input_name(struct rmi_device *rmi_dev,
				struct input_dev *input)
{
	struct rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	const char *device_name = rmi_f01_get_product_ID(data->f01_container);
	char *name;

	name = devm_kasprintf(&rmi_dev->dev, GFP_KERNEL,
			      "Synaptics %s", device_name);
	if (!name)
		return;

	input->name = name;
}
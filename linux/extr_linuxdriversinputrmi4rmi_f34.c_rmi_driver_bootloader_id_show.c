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
struct rmi_driver_data {struct rmi_function* f34_container; } ;
struct f34_data {int bl_version; int /*<<< orphan*/ * bootloader_id; } ;
struct device_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t rmi_driver_bootloader_id_show(struct device *dev,
					     struct device_attribute *dattr,
					     char *buf)
{
	struct rmi_driver_data *data = dev_get_drvdata(dev);
	struct rmi_function *fn = data->f34_container;
	struct f34_data *f34;

	if (fn) {
		f34 = dev_get_drvdata(&fn->dev);

		if (f34->bl_version == 5)
			return scnprintf(buf, PAGE_SIZE, "%c%c\n",
					 f34->bootloader_id[0],
					 f34->bootloader_id[1]);
		else
			return scnprintf(buf, PAGE_SIZE, "V%d.%d\n",
					 f34->bootloader_id[1],
					 f34->bootloader_id[0]);
	}

	return 0;
}
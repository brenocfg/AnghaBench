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
typedef  int u8 ;
struct rmi_driver_data {int bootloader_mode; } ;
struct rmi_device {int /*<<< orphan*/  dev; } ;
struct pdt_entry {int function_number; int function_version; int /*<<< orphan*/  data_base_addr; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct rmi_driver_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int rmi_read (struct rmi_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int rmi_check_bootloader_mode(struct rmi_device *rmi_dev,
				     const struct pdt_entry *pdt)
{
	struct rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	int ret;
	u8 status;

	if (pdt->function_number == 0x34 && pdt->function_version > 1) {
		ret = rmi_read(rmi_dev, pdt->data_base_addr, &status);
		if (ret) {
			dev_err(&rmi_dev->dev,
				"Failed to read F34 status: %d.\n", ret);
			return ret;
		}

		if (status & BIT(7))
			data->bootloader_mode = true;
	} else if (pdt->function_number == 0x01) {
		ret = rmi_read(rmi_dev, pdt->data_base_addr, &status);
		if (ret) {
			dev_err(&rmi_dev->dev,
				"Failed to read F01 status: %d.\n", ret);
			return ret;
		}

		if (status & BIT(6))
			data->bootloader_mode = true;
	}

	return 0;
}
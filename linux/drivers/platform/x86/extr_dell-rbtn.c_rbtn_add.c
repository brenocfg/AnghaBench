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
struct rbtn_data {int type; } ;
struct acpi_device {struct rbtn_data* driver_data; int /*<<< orphan*/  dev; } ;
typedef  enum rbtn_type { ____Placeholder_rbtn_type } rbtn_type ;
struct TYPE_2__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  RBTN_SLIDER 129 
#define  RBTN_TOGGLE 128 
 int RBTN_UNKNOWN ; 
 int /*<<< orphan*/  auto_remove_rfkill ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct rbtn_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int rbtn_acquire (struct acpi_device*,int) ; 
 TYPE_1__ rbtn_chain_head ; 
 int rbtn_check (struct acpi_device*) ; 
 int rbtn_input_init (struct rbtn_data*) ; 
 int rbtn_rfkill_init (struct acpi_device*) ; 

__attribute__((used)) static int rbtn_add(struct acpi_device *device)
{
	struct rbtn_data *rbtn_data;
	enum rbtn_type type;
	int ret = 0;

	type = rbtn_check(device);
	if (type == RBTN_UNKNOWN) {
		dev_info(&device->dev, "Unknown device type\n");
		return -EINVAL;
	}

	ret = rbtn_acquire(device, true);
	if (ret < 0) {
		dev_err(&device->dev, "Cannot enable device\n");
		return ret;
	}

	rbtn_data = devm_kzalloc(&device->dev, sizeof(*rbtn_data), GFP_KERNEL);
	if (!rbtn_data)
		return -ENOMEM;

	rbtn_data->type = type;
	device->driver_data = rbtn_data;

	switch (rbtn_data->type) {
	case RBTN_TOGGLE:
		ret = rbtn_input_init(rbtn_data);
		break;
	case RBTN_SLIDER:
		if (auto_remove_rfkill && rbtn_chain_head.head)
			ret = 0;
		else
			ret = rbtn_rfkill_init(device);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;

}
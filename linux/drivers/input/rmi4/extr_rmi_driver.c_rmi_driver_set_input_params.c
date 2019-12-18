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
struct rmi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bustype; int /*<<< orphan*/  vendor; } ;
struct input_dev {TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_RMI ; 
 int /*<<< orphan*/  SYNAPTICS_INPUT_DEVICE_NAME ; 
 int /*<<< orphan*/  SYNAPTICS_VENDOR_ID ; 

__attribute__((used)) static int rmi_driver_set_input_params(struct rmi_device *rmi_dev,
				struct input_dev *input)
{
	input->name = SYNAPTICS_INPUT_DEVICE_NAME;
	input->id.vendor  = SYNAPTICS_VENDOR_ID;
	input->id.bustype = BUS_RMI;
	return 0;
}
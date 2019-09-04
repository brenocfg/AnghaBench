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
struct input_handler {int dummy; } ;
struct input_handle {char* name; struct input_handler* handler; struct input_dev* dev; } ;
struct input_device_id {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int input_open_device (struct input_handle*) ; 
 int input_register_handle (struct input_handle*) ; 
 int /*<<< orphan*/  input_unregister_handle (struct input_handle*) ; 
 int /*<<< orphan*/  kfree (struct input_handle*) ; 
 struct input_handle* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int apmpower_connect(struct input_handler *handler,
					  struct input_dev *dev,
					  const struct input_device_id *id)
{
	struct input_handle *handle;
	int error;

	handle = kzalloc(sizeof(struct input_handle), GFP_KERNEL);
	if (!handle)
		return -ENOMEM;

	handle->dev = dev;
	handle->handler = handler;
	handle->name = "apm-power";

	error = input_register_handle(handle);
	if (error) {
		pr_err("Failed to register input power handler, error %d\n",
		       error);
		kfree(handle);
		return error;
	}

	error = input_open_device(handle);
	if (error) {
		pr_err("Failed to open input power device, error %d\n", error);
		input_unregister_handle(handle);
		kfree(handle);
		return error;
	}

	return 0;
}
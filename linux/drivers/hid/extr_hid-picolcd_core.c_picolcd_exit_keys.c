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
struct picolcd_data {struct input_dev* input_keys; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 

__attribute__((used)) static void picolcd_exit_keys(struct picolcd_data *data)
{
	struct input_dev *idev = data->input_keys;

	data->input_keys = NULL;
	if (idev)
		input_unregister_device(idev);
}
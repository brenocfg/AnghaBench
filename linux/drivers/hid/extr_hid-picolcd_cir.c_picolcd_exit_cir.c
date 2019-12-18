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
struct rc_dev {int dummy; } ;
struct picolcd_data {struct rc_dev* rc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  rc_unregister_device (struct rc_dev*) ; 

void picolcd_exit_cir(struct picolcd_data *data)
{
	struct rc_dev *rdev = data->rc_dev;

	data->rc_dev = NULL;
	rc_unregister_device(rdev);
}
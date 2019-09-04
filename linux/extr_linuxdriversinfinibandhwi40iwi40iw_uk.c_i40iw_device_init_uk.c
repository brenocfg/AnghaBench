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
struct i40iw_dev_uk {int /*<<< orphan*/  ops_uk; } ;

/* Variables and functions */
 int /*<<< orphan*/  iw_device_uk_ops ; 

void i40iw_device_init_uk(struct i40iw_dev_uk *dev)
{
	dev->ops_uk = iw_device_uk_ops;
}
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
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ksz8795_dev_ops ; 
 int ksz_switch_register (struct ksz_device*,int /*<<< orphan*/ *) ; 

int ksz8795_switch_register(struct ksz_device *dev)
{
	return ksz_switch_register(dev, &ksz8795_dev_ops);
}
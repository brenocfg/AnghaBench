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
typedef  size_t uint32_t ;
struct fsi_device {size_t size; size_t addr; int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 int EINVAL ; 
 int fsi_slave_write (int /*<<< orphan*/ ,size_t,void const*,size_t) ; 

int fsi_device_write(struct fsi_device *dev, uint32_t addr, const void *val,
		size_t size)
{
	if (addr > dev->size || size > dev->size || addr > dev->size - size)
		return -EINVAL;

	return fsi_slave_write(dev->slave, dev->addr + addr, val, size);
}
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
struct TYPE_2__ {int /*<<< orphan*/  in; } ;
struct i3c_priv_xfer {TYPE_1__ data; int /*<<< orphan*/  len; } ;
struct i3c_device {int /*<<< orphan*/  bus; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  i3c_bus_normaluse_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_bus_normaluse_unlock (int /*<<< orphan*/ ) ; 
 int i3c_dev_do_priv_xfers_locked (int /*<<< orphan*/ ,struct i3c_priv_xfer*,int) ; 

int i3c_device_do_priv_xfers(struct i3c_device *dev,
			     struct i3c_priv_xfer *xfers,
			     int nxfers)
{
	int ret, i;

	if (nxfers < 1)
		return 0;

	for (i = 0; i < nxfers; i++) {
		if (!xfers[i].len || !xfers[i].data.in)
			return -EINVAL;
	}

	i3c_bus_normaluse_lock(dev->bus);
	ret = i3c_dev_do_priv_xfers_locked(dev->desc, xfers, nxfers);
	i3c_bus_normaluse_unlock(dev->bus);

	return ret;
}
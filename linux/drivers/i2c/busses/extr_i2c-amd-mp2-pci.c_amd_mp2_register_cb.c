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
struct amd_mp2_dev {struct amd_i2c_common** busses; } ;
struct amd_i2c_common {int bus_id; struct amd_mp2_dev* mp2_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ndev_dev (struct amd_mp2_dev*) ; 

int amd_mp2_register_cb(struct amd_i2c_common *i2c_common)
{
	struct amd_mp2_dev *privdata = i2c_common->mp2_dev;

	if (i2c_common->bus_id > 1)
		return -EINVAL;

	if (privdata->busses[i2c_common->bus_id]) {
		dev_err(ndev_dev(privdata),
			"Bus %d already taken!\n", i2c_common->bus_id);
		return -EINVAL;
	}

	privdata->busses[i2c_common->bus_id] = i2c_common;

	return 0;
}
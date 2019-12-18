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
struct amd_mp2_dev {int /*<<< orphan*/ ** busses; } ;
struct amd_i2c_common {size_t bus_id; struct amd_mp2_dev* mp2_dev; } ;

/* Variables and functions */

int amd_mp2_unregister_cb(struct amd_i2c_common *i2c_common)
{
	struct amd_mp2_dev *privdata = i2c_common->mp2_dev;

	privdata->busses[i2c_common->bus_id] = NULL;

	return 0;
}
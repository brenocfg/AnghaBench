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
struct amd_mp2_dev {int dummy; } ;
struct amd_i2c_common {scalar_t__ reqcmd; int /*<<< orphan*/  bus_id; struct amd_mp2_dev* mp2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __amd_mp2_process_event (struct amd_i2c_common*) ; 
 int /*<<< orphan*/  amd_mp2_c2p_mutex_unlock (struct amd_i2c_common*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_none ; 
 int /*<<< orphan*/  ndev_dev (struct amd_mp2_dev*) ; 
 scalar_t__ unlikely (int) ; 

void amd_mp2_process_event(struct amd_i2c_common *i2c_common)
{
	struct amd_mp2_dev *privdata = i2c_common->mp2_dev;

	if (unlikely(i2c_common->reqcmd == i2c_none)) {
		dev_warn(ndev_dev(privdata),
			 "received msg but no cmd was sent (bus = %d)!\n",
			 i2c_common->bus_id);
		return;
	}

	__amd_mp2_process_event(i2c_common);

	i2c_common->reqcmd = i2c_none;
	amd_mp2_c2p_mutex_unlock(i2c_common);
}
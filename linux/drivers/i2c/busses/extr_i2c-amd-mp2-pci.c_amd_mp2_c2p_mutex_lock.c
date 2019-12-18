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
struct amd_mp2_dev {int /*<<< orphan*/  c2p_lock_busid; int /*<<< orphan*/  c2p_lock; } ;
struct amd_i2c_common {int /*<<< orphan*/  bus_id; struct amd_mp2_dev* mp2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amd_mp2_c2p_mutex_lock(struct amd_i2c_common *i2c_common)
{
	struct amd_mp2_dev *privdata = i2c_common->mp2_dev;

	/* there is only one data mailbox for two i2c adapters */
	mutex_lock(&privdata->c2p_lock);
	privdata->c2p_lock_busid = i2c_common->bus_id;
}
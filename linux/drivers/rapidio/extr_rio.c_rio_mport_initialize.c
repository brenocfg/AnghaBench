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
struct rio_mport {int /*<<< orphan*/  pwrites; scalar_t__ pwe_refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/ * nscan; scalar_t__ id; int /*<<< orphan*/  host_deviceid; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RIO_DEVICE_INITIALIZING ; 
 scalar_t__ RIO_MAX_MPORTS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ next_portid ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rio_get_hdid (scalar_t__) ; 

int rio_mport_initialize(struct rio_mport *mport)
{
	if (next_portid >= RIO_MAX_MPORTS) {
		pr_err("RIO: reached specified max number of mports\n");
		return -ENODEV;
	}

	atomic_set(&mport->state, RIO_DEVICE_INITIALIZING);
	mport->id = next_portid++;
	mport->host_deviceid = rio_get_hdid(mport->id);
	mport->nscan = NULL;
	mutex_init(&mport->lock);
	mport->pwe_refcnt = 0;
	INIT_LIST_HEAD(&mport->pwrites);

	return 0;
}
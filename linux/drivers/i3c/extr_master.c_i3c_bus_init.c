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
struct TYPE_2__ {int /*<<< orphan*/  i3c; int /*<<< orphan*/  i2c; } ;
struct i3c_bus {int id; int /*<<< orphan*/  mode; TYPE_1__ devs; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I3C_BUS_MODE_PURE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3c_bus_idr ; 
 int /*<<< orphan*/  i3c_bus_init_addrslots (struct i3c_bus*) ; 
 int /*<<< orphan*/  i3c_core_lock ; 
 int idr_alloc (int /*<<< orphan*/ *,struct i3c_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i3c_bus_init(struct i3c_bus *i3cbus)
{
	int ret;

	init_rwsem(&i3cbus->lock);
	INIT_LIST_HEAD(&i3cbus->devs.i2c);
	INIT_LIST_HEAD(&i3cbus->devs.i3c);
	i3c_bus_init_addrslots(i3cbus);
	i3cbus->mode = I3C_BUS_MODE_PURE;

	mutex_lock(&i3c_core_lock);
	ret = idr_alloc(&i3c_bus_idr, i3cbus, 0, 0, GFP_KERNEL);
	mutex_unlock(&i3c_core_lock);

	if (ret < 0)
		return ret;

	i3cbus->id = ret;

	return 0;
}
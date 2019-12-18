#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  uuid; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* to_tee_client_device (struct device*) ; 

__attribute__((used)) static int tee_client_device_uevent(struct device *dev,
				    struct kobj_uevent_env *env)
{
	uuid_t *dev_id = &to_tee_client_device(dev)->id.uuid;

	return add_uevent_var(env, "MODALIAS=tee:%pUb", dev_id);
}
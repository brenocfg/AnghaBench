#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct typec_altmode {TYPE_1__ dev; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct altmode {TYPE_3__ adev; int /*<<< orphan*/  nh; struct altmode* partner; } ;
struct TYPE_5__ {int (* notify ) (TYPE_3__*,unsigned long,void*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,void*) ; 
 int is_typec_port (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,unsigned long,void*) ; 
 struct altmode* to_altmode (struct typec_altmode*) ; 
 int typec_altmode_set_mux (struct altmode*,int /*<<< orphan*/ ) ; 

int typec_altmode_notify(struct typec_altmode *adev,
			 unsigned long conf, void *data)
{
	bool is_port;
	struct altmode *altmode;
	struct altmode *partner;
	int ret;

	if (!adev)
		return 0;

	altmode = to_altmode(adev);

	if (!altmode->partner)
		return -ENODEV;

	is_port = is_typec_port(adev->dev.parent);
	partner = altmode->partner;

	ret = typec_altmode_set_mux(is_port ? altmode : partner, (u8)conf);
	if (ret)
		return ret;

	blocking_notifier_call_chain(is_port ? &altmode->nh : &partner->nh,
				     conf, data);

	if (partner->adev.ops && partner->adev.ops->notify)
		return partner->adev.ops->notify(&partner->adev, conf, data);

	return 0;
}
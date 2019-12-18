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
struct typec_altmode {TYPE_1__* ops; scalar_t__ active; } ;
struct altmode {struct typec_altmode adev; } ;
struct TYPE_4__ {struct altmode* partner; } ;
struct TYPE_3__ {int (* enter ) (struct typec_altmode*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TYPEC_STATE_SAFE ; 
 int stub1 (struct typec_altmode*) ; 
 TYPE_2__* to_altmode (struct typec_altmode*) ; 
 int typec_altmode_set_state (struct typec_altmode*,int /*<<< orphan*/ ) ; 

int typec_altmode_enter(struct typec_altmode *adev)
{
	struct altmode *partner = to_altmode(adev)->partner;
	struct typec_altmode *pdev = &partner->adev;
	int ret;

	if (!adev || adev->active)
		return 0;

	if (!pdev->ops || !pdev->ops->enter)
		return -EOPNOTSUPP;

	/* Moving to USB Safe State */
	ret = typec_altmode_set_state(adev, TYPEC_STATE_SAFE);
	if (ret)
		return ret;

	/* Enter Mode */
	return pdev->ops->enter(pdev);
}
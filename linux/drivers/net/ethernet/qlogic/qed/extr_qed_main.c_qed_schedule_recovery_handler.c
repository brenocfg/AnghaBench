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
struct qed_hwfn {TYPE_2__* cdev; } ;
struct qed_common_cb_ops {int /*<<< orphan*/  (* schedule_recovery_handler ) (void*) ;} ;
struct TYPE_3__ {struct qed_common_cb_ops* common; } ;
struct TYPE_4__ {void* ops_cookie; TYPE_1__ protocol_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*) ; 

void qed_schedule_recovery_handler(struct qed_hwfn *p_hwfn)
{
	struct qed_common_cb_ops *ops = p_hwfn->cdev->protocol_ops.common;
	void *cookie = p_hwfn->cdev->ops_cookie;

	if (ops && ops->schedule_recovery_handler)
		ops->schedule_recovery_handler(cookie);
}
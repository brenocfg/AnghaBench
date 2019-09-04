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
typedef  int /*<<< orphan*/  u32 ;
struct qed_hwfn {TYPE_3__* p_dcbx_info; TYPE_2__* cdev; } ;
struct qed_common_cb_ops {int /*<<< orphan*/  (* dcbx_aen ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  get; } ;
struct TYPE_4__ {struct qed_common_cb_ops* common; } ;
struct TYPE_5__ {void* ops_cookie; TYPE_1__ protocol_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_dcbx_aen(struct qed_hwfn *hwfn, u32 mib_type)
{
	struct qed_common_cb_ops *op = hwfn->cdev->protocol_ops.common;
	void *cookie = hwfn->cdev->ops_cookie;

	if (cookie && op->dcbx_aen)
		op->dcbx_aen(cookie, &hwfn->p_dcbx_info->get, mib_type);
}
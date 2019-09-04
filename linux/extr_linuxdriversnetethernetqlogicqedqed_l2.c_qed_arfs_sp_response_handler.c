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
typedef  union event_ring_data {int dummy; } event_ring_data ;
typedef  int /*<<< orphan*/  u8 ;
struct qed_hwfn {TYPE_2__* cdev; } ;
struct qed_common_cb_ops {int /*<<< orphan*/  (* arfs_filter_op ) (void*,void*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct qed_common_cb_ops* common; } ;
struct TYPE_4__ {void* ops_cookie; TYPE_1__ protocol_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qed_arfs_sp_response_handler(struct qed_hwfn *p_hwfn,
			     void *cookie,
			     union event_ring_data *data, u8 fw_return_code)
{
	struct qed_common_cb_ops *op = p_hwfn->cdev->protocol_ops.common;
	void *dev = p_hwfn->cdev->ops_cookie;

	op->arfs_filter_op(dev, cookie, fw_return_code);
}
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
struct qed_fcoe_cb_ops {int dummy; } ;
struct TYPE_2__ {struct qed_fcoe_cb_ops* fcoe; } ;
struct qed_dev {void* ops_cookie; TYPE_1__ protocol_ops; } ;

/* Variables and functions */

__attribute__((used)) static void qed_register_fcoe_ops(struct qed_dev *cdev,
				  struct qed_fcoe_cb_ops *ops, void *cookie)
{
	cdev->protocol_ops.fcoe = ops;
	cdev->ops_cookie = cookie;
}
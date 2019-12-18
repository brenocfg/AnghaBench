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
struct qed_ll2_cb_ops {int dummy; } ;
struct qed_dev {TYPE_1__* ll2; } ;
struct TYPE_2__ {void* cb_cookie; struct qed_ll2_cb_ops const* cbs; } ;

/* Variables and functions */

__attribute__((used)) static void qed_ll2_register_cb_ops(struct qed_dev *cdev,
				    const struct qed_ll2_cb_ops *ops,
				    void *cookie)
{
	cdev->ll2->cbs = ops;
	cdev->ll2->cb_cookie = cookie;
}
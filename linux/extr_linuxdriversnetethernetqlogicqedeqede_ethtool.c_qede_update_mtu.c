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
struct TYPE_4__ {int /*<<< orphan*/  mtu; } ;
struct qede_reload_args {TYPE_2__ u; } ;
struct qede_dev {TYPE_1__* ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */

__attribute__((used)) static void qede_update_mtu(struct qede_dev *edev,
			    struct qede_reload_args *args)
{
	edev->ndev->mtu = args->u.mtu;
}
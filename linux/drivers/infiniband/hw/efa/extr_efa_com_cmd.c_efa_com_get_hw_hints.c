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
struct efa_com_get_hw_hints_result {int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  mmio_read_timeout; int /*<<< orphan*/  driver_watchdog_timeout; int /*<<< orphan*/  admin_completion_timeout; } ;
struct efa_com_dev {int /*<<< orphan*/  efa_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  mmio_read_timeout; int /*<<< orphan*/  driver_watchdog_timeout; int /*<<< orphan*/  admin_completion_timeout; } ;
struct TYPE_3__ {TYPE_2__ hw_hints; } ;
struct efa_admin_get_feature_resp {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_ADMIN_HW_HINTS ; 
 int efa_com_get_feature (struct efa_com_dev*,struct efa_admin_get_feature_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 

int efa_com_get_hw_hints(struct efa_com_dev *edev,
			 struct efa_com_get_hw_hints_result *result)
{
	struct efa_admin_get_feature_resp resp;
	int err;

	err = efa_com_get_feature(edev, &resp, EFA_ADMIN_HW_HINTS);
	if (err) {
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to get hw hints %d\n", err);
		return err;
	}

	result->admin_completion_timeout = resp.u.hw_hints.admin_completion_timeout;
	result->driver_watchdog_timeout = resp.u.hw_hints.driver_watchdog_timeout;
	result->mmio_read_timeout = resp.u.hw_hints.mmio_read_timeout;
	result->poll_interval = resp.u.hw_hints.poll_interval;

	return 0;
}
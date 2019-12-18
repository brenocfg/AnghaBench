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
struct TYPE_4__ {scalar_t__ completion_timeout; scalar_t__ poll_interval; } ;
struct TYPE_3__ {int mmio_read_timeout; } ;
struct efa_com_dev {TYPE_2__ aq; TYPE_1__ mmio_read; } ;
struct efa_dev {struct efa_com_dev edev; } ;
struct efa_com_get_hw_hints_result {int mmio_read_timeout; scalar_t__ admin_completion_timeout; scalar_t__ poll_interval; } ;

/* Variables and functions */

__attribute__((used)) static void efa_update_hw_hints(struct efa_dev *dev,
				struct efa_com_get_hw_hints_result *hw_hints)
{
	struct efa_com_dev *edev = &dev->edev;

	if (hw_hints->mmio_read_timeout)
		edev->mmio_read.mmio_read_timeout =
			hw_hints->mmio_read_timeout * 1000;

	if (hw_hints->poll_interval)
		edev->aq.poll_interval = hw_hints->poll_interval;

	if (hw_hints->admin_completion_timeout)
		edev->aq.completion_timeout =
			hw_hints->admin_completion_timeout;
}
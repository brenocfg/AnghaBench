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
struct TYPE_2__ {int /*<<< orphan*/  scan_work; int /*<<< orphan*/  reset_work; } ;
struct nvme_dev {TYPE_1__ ctrl; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_put_ctrl (TYPE_1__*) ; 

__attribute__((used)) static void nvme_async_probe(void *data, async_cookie_t cookie)
{
	struct nvme_dev *dev = data;

	flush_work(&dev->ctrl.reset_work);
	flush_work(&dev->ctrl.scan_work);
	nvme_put_ctrl(&dev->ctrl);
}
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
struct qxl_head {int y; int x; int width; int height; } ;
struct qxl_device {TYPE_2__* monitors_config; TYPE_1__* ram_header; } ;
struct TYPE_4__ {int count; struct qxl_head* heads; } ;
struct TYPE_3__ {int /*<<< orphan*/  monitors_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  qxl_io_monitors_config (struct qxl_device*) ; 

__attribute__((used)) static void qxl_send_monitors_config(struct qxl_device *qdev)
{
	int i;

	BUG_ON(!qdev->ram_header->monitors_config);

	if (qdev->monitors_config->count == 0)
		return;

	for (i = 0 ; i < qdev->monitors_config->count ; ++i) {
		struct qxl_head *head = &qdev->monitors_config->heads[i];

		if (head->y > 8192 || head->x > 8192 ||
		    head->width > 8192 || head->height > 8192) {
			DRM_ERROR("head %d wrong: %dx%d+%d+%d\n",
				  i, head->width, head->height,
				  head->x, head->y);
			return;
		}
	}
	qxl_io_monitors_config(qdev);
}
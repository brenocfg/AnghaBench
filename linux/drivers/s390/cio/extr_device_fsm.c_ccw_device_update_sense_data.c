#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dev_model; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  cu_model; int /*<<< orphan*/  cu_type; } ;
struct ccw_device {TYPE_3__* private; TYPE_4__ id; } ;
struct TYPE_7__ {TYPE_2__* dma_area; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_model; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  cu_model; int /*<<< orphan*/  cu_type; } ;
struct TYPE_6__ {TYPE_1__ senseid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void ccw_device_update_sense_data(struct ccw_device *cdev)
{
	memset(&cdev->id, 0, sizeof(cdev->id));
	cdev->id.cu_type = cdev->private->dma_area->senseid.cu_type;
	cdev->id.cu_model = cdev->private->dma_area->senseid.cu_model;
	cdev->id.dev_type = cdev->private->dma_area->senseid.dev_type;
	cdev->id.dev_model = cdev->private->dma_area->senseid.dev_model;
}
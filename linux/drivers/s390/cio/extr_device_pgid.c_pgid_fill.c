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
struct pgid {int dummy; } ;
struct ccw_device {TYPE_2__* private; } ;
struct TYPE_4__ {TYPE_1__* dma_area; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct pgid*,int) ; 

__attribute__((used)) static void pgid_fill(struct ccw_device *cdev, struct pgid *pgid)
{
	int i;

	for (i = 0; i < 8; i++)
		memcpy(&cdev->private->dma_area->pgid[i], pgid,
		       sizeof(struct pgid));
}
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
struct gendisk {TYPE_2__* queue; } ;
struct blk_integrity {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  integrity; TYPE_1__* backing_dev_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_CAP_STABLE_WRITES ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void blk_integrity_unregister(struct gendisk *disk)
{
	disk->queue->backing_dev_info->capabilities &= ~BDI_CAP_STABLE_WRITES;
	memset(&disk->queue->integrity, 0, sizeof(struct blk_integrity));
}
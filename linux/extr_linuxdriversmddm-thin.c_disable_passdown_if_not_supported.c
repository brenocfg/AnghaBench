#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct queue_limits {scalar_t__ max_discard_sectors; } ;
struct TYPE_4__ {int discard_passdown; } ;
struct pool_c {TYPE_1__ adjusted_pf; TYPE_2__* data_dev; struct pool* pool; } ;
struct pool {scalar_t__ sectors_per_block; } ;
struct block_device {int dummy; } ;
struct TYPE_6__ {struct queue_limits limits; } ;
struct TYPE_5__ {struct block_device* bdev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_3__* bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  bdevname (struct block_device*,char*) ; 
 int /*<<< orphan*/  data_dev_supports_discard (struct pool_c*) ; 

__attribute__((used)) static void disable_passdown_if_not_supported(struct pool_c *pt)
{
	struct pool *pool = pt->pool;
	struct block_device *data_bdev = pt->data_dev->bdev;
	struct queue_limits *data_limits = &bdev_get_queue(data_bdev)->limits;
	const char *reason = NULL;
	char buf[BDEVNAME_SIZE];

	if (!pt->adjusted_pf.discard_passdown)
		return;

	if (!data_dev_supports_discard(pt))
		reason = "discard unsupported";

	else if (data_limits->max_discard_sectors < pool->sectors_per_block)
		reason = "max discard sectors smaller than a block";

	if (reason) {
		DMWARN("Data device (%s) %s: Disabling discard passdown.", bdevname(data_bdev, buf), reason);
		pt->adjusted_pf.discard_passdown = false;
	}
}
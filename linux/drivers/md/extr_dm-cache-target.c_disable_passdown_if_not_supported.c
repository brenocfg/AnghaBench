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
struct TYPE_5__ {int discard_passdown; } ;
struct cache {scalar_t__ sectors_per_block; TYPE_2__ features; TYPE_1__* origin_dev; } ;
struct block_device {int dummy; } ;
struct TYPE_6__ {struct queue_limits limits; } ;
struct TYPE_4__ {struct block_device* bdev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_3__* bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  bdevname (struct block_device*,char*) ; 
 int /*<<< orphan*/  origin_dev_supports_discard (struct block_device*) ; 

__attribute__((used)) static void disable_passdown_if_not_supported(struct cache *cache)
{
	struct block_device *origin_bdev = cache->origin_dev->bdev;
	struct queue_limits *origin_limits = &bdev_get_queue(origin_bdev)->limits;
	const char *reason = NULL;
	char buf[BDEVNAME_SIZE];

	if (!cache->features.discard_passdown)
		return;

	if (!origin_dev_supports_discard(origin_bdev))
		reason = "discard unsupported";

	else if (origin_limits->max_discard_sectors < cache->sectors_per_block)
		reason = "max discard sectors smaller than a block";

	if (reason) {
		DMWARN("Origin device (%s) %s: Disabling discard passdown.",
		       bdevname(origin_bdev, buf), reason);
		cache->features.discard_passdown = false;
	}
}
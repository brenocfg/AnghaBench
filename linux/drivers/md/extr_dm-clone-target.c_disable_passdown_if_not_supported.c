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
struct queue_limits {scalar_t__ max_discard_sectors; } ;
struct clone {scalar_t__ region_size; int /*<<< orphan*/  flags; TYPE_1__* dest_dev; } ;
struct block_device {int dummy; } ;
struct TYPE_4__ {struct queue_limits limits; } ;
struct TYPE_3__ {struct block_device* bdev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  DM_CLONE_DISCARD_PASSDOWN ; 
 TYPE_2__* bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  bdev_supports_discards (struct block_device*) ; 
 int /*<<< orphan*/  bdevname (struct block_device*,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_passdown_if_not_supported(struct clone *clone)
{
	struct block_device *dest_dev = clone->dest_dev->bdev;
	struct queue_limits *dest_limits = &bdev_get_queue(dest_dev)->limits;
	const char *reason = NULL;
	char buf[BDEVNAME_SIZE];

	if (!test_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags))
		return;

	if (!bdev_supports_discards(dest_dev))
		reason = "discard unsupported";
	else if (dest_limits->max_discard_sectors < clone->region_size)
		reason = "max discard sectors smaller than a region";

	if (reason) {
		DMWARN("Destination device (%s) %s: Disabling discard passdown.",
		       bdevname(dest_dev, buf), reason);
		clear_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags);
	}
}
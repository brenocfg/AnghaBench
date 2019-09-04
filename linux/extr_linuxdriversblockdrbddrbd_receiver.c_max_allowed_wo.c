#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drbd_backing_dev {int /*<<< orphan*/  disk_conf; } ;
struct disk_conf {int /*<<< orphan*/  disk_drain; int /*<<< orphan*/  disk_flushes; } ;
typedef  enum write_ordering_e { ____Placeholder_write_ordering_e } write_ordering_e ;

/* Variables and functions */
 int WO_BDEV_FLUSH ; 
 int WO_DRAIN_IO ; 
 int WO_NONE ; 
 struct disk_conf* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum write_ordering_e
max_allowed_wo(struct drbd_backing_dev *bdev, enum write_ordering_e wo)
{
	struct disk_conf *dc;

	dc = rcu_dereference(bdev->disk_conf);

	if (wo == WO_BDEV_FLUSH && !dc->disk_flushes)
		wo = WO_DRAIN_IO;
	if (wo == WO_DRAIN_IO && !dc->disk_drain)
		wo = WO_NONE;

	return wo;
}
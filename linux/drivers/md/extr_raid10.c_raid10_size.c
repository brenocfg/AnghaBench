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
struct TYPE_3__ {int chunk_shift; int /*<<< orphan*/  near_copies; int /*<<< orphan*/  far_copies; int /*<<< orphan*/  raid_disks; } ;
struct TYPE_4__ {int /*<<< orphan*/  raid_disks; } ;
struct r10conf {int dev_sectors; TYPE_1__ geo; TYPE_2__ prev; } ;
struct mddev {struct r10conf* private; } ;
typedef  int sector_t ;

/* Variables and functions */
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_div (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sector_t
raid10_size(struct mddev *mddev, sector_t sectors, int raid_disks)
{
	sector_t size;
	struct r10conf *conf = mddev->private;

	if (!raid_disks)
		raid_disks = min(conf->geo.raid_disks,
				 conf->prev.raid_disks);
	if (!sectors)
		sectors = conf->dev_sectors;

	size = sectors >> conf->geo.chunk_shift;
	sector_div(size, conf->geo.far_copies);
	size = size * raid_disks;
	sector_div(size, conf->geo.near_copies);

	return size << conf->geo.chunk_shift;
}
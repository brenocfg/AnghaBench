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
struct nullb_device {struct blk_zone* zones; } ;
struct nullb_cmd {TYPE_1__* nq; } ;
struct blk_zone {int /*<<< orphan*/  start; int /*<<< orphan*/  wp; int /*<<< orphan*/  cond; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {struct nullb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_ZONE_COND_EMPTY ; 
 unsigned int null_zone_no (struct nullb_device*,int /*<<< orphan*/ ) ; 

void null_zone_reset(struct nullb_cmd *cmd, sector_t sector)
{
	struct nullb_device *dev = cmd->nq->dev;
	unsigned int zno = null_zone_no(dev, sector);
	struct blk_zone *zone = &dev->zones[zno];

	zone->cond = BLK_ZONE_COND_EMPTY;
	zone->wp = zone->start;
}
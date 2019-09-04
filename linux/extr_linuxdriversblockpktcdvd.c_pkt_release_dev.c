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
struct pktcdvd_device {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  MAX_SPEED ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pkt_dbg (int,struct pktcdvd_device*,char*) ; 
 scalar_t__ pkt_flush_cache (struct pktcdvd_device*) ; 
 int /*<<< orphan*/  pkt_lock_door (struct pktcdvd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_set_speed (struct pktcdvd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_shrink_pktlist (struct pktcdvd_device*) ; 

__attribute__((used)) static void pkt_release_dev(struct pktcdvd_device *pd, int flush)
{
	if (flush && pkt_flush_cache(pd))
		pkt_dbg(1, pd, "not flushing cache\n");

	pkt_lock_door(pd, 0);

	pkt_set_speed(pd, MAX_SPEED, MAX_SPEED);
	blkdev_put(pd->bdev, FMODE_READ | FMODE_EXCL);

	pkt_shrink_pktlist(pd);
}
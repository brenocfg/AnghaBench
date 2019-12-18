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
typedef  int u8 ;
struct b53_device {int serdes_lane; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_SERDES_LANE ; 
 int /*<<< orphan*/  SERDES_XGXSBLK0_BLOCKADDRESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  b53_serdes_write_blk (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b53_serdes_set_lane(struct b53_device *dev, u8 lane)
{
	if (dev->serdes_lane == lane)
		return;

	WARN_ON(lane > 1);

	b53_serdes_write_blk(dev, B53_SERDES_LANE,
			     SERDES_XGXSBLK0_BLOCKADDRESS, lane);
	dev->serdes_lane = lane;
}
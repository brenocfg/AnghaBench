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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b53_serdes_read_blk (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_serdes_set_lane (struct b53_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 b53_serdes_read(struct b53_device *dev, u8 lane,
			   u8 offset, u16 block)
{
	b53_serdes_set_lane(dev, lane);
	return b53_serdes_read_blk(dev, offset, block);
}
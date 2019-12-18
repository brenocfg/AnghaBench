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
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int PORT_QUEUE_SPLIT_1 ; 
 int PORT_QUEUE_SPLIT_2 ; 
 int PORT_QUEUE_SPLIT_4 ; 
 int /*<<< orphan*/  PORT_QUEUE_SPLIT_H ; 
 int /*<<< orphan*/  PORT_QUEUE_SPLIT_L ; 
 int /*<<< orphan*/  P_DROP_TAG_CTRL ; 
 int /*<<< orphan*/  REG_PORT_CTRL_0 ; 
 int /*<<< orphan*/  REG_SW_CTRL_19 ; 
 int /*<<< orphan*/  SW_OUT_RATE_LIMIT_QUEUE_BASED ; 
 int /*<<< orphan*/  ksz_cfg (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_pread8 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz_pwrite8 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksz8795_set_prio_queue(struct ksz_device *dev, int port, int queue)
{
	u8 hi, lo;

	/* Number of queues can only be 1, 2, or 4. */
	switch (queue) {
	case 4:
	case 3:
		queue = PORT_QUEUE_SPLIT_4;
		break;
	case 2:
		queue = PORT_QUEUE_SPLIT_2;
		break;
	default:
		queue = PORT_QUEUE_SPLIT_1;
	}
	ksz_pread8(dev, port, REG_PORT_CTRL_0, &lo);
	ksz_pread8(dev, port, P_DROP_TAG_CTRL, &hi);
	lo &= ~PORT_QUEUE_SPLIT_L;
	if (queue & PORT_QUEUE_SPLIT_2)
		lo |= PORT_QUEUE_SPLIT_L;
	hi &= ~PORT_QUEUE_SPLIT_H;
	if (queue & PORT_QUEUE_SPLIT_4)
		hi |= PORT_QUEUE_SPLIT_H;
	ksz_pwrite8(dev, port, REG_PORT_CTRL_0, lo);
	ksz_pwrite8(dev, port, P_DROP_TAG_CTRL, hi);

	/* Default is port based for egress rate limit. */
	if (queue != PORT_QUEUE_SPLIT_1)
		ksz_cfg(dev, REG_SW_CTRL_19, SW_OUT_RATE_LIMIT_QUEUE_BASED,
			true);
}
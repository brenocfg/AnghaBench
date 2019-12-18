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
typedef  scalar_t__ u32 ;
struct hnae_queue {TYPE_1__* dev; int /*<<< orphan*/  tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int HNS_MAX_WAIT_CNT ; 
 int /*<<< orphan*/  RCB_REG_HEAD ; 
 int /*<<< orphan*/  RCB_REG_TAIL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dsaf_read_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int hns_rcb_wait_tx_ring_clean(struct hnae_queue *qs)
{
	u32 head, tail;
	int wait_cnt;

	tail = dsaf_read_dev(&qs->tx_ring, RCB_REG_TAIL);
	wait_cnt = 0;
	while (wait_cnt++ < HNS_MAX_WAIT_CNT) {
		head = dsaf_read_dev(&qs->tx_ring, RCB_REG_HEAD);
		if (tail == head)
			break;

		usleep_range(100, 200);
	}

	if (wait_cnt >= HNS_MAX_WAIT_CNT) {
		dev_err(qs->dev->dev, "rcb wait timeout, head not equal to tail.\n");
		return -EBUSY;
	}

	return 0;
}
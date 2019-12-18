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
typedef  scalar_t__ u32 ;
struct hnae_queue {int /*<<< orphan*/  handle; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_index; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ RCB_RESET_TRY_TIMES ; 
 scalar_t__ RCB_RESET_WAIT_TIMES ; 
 int /*<<< orphan*/  RCB_RING_COULD_BE_RST ; 
 int /*<<< orphan*/  RCB_RING_PREFETCH_EN_REG ; 
 int /*<<< orphan*/  RCB_RING_T0_BE_RST ; 
 int /*<<< orphan*/  RCB_RING_TX_RING_FBDNUM_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dsaf_read_dev (struct hnae_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct hnae_queue*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* hns_ae_get_vf_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void hns_rcb_reset_ring_hw(struct hnae_queue *q)
{
	u32 wait_cnt;
	u32 try_cnt = 0;
	u32 could_ret;

	u32 tx_fbd_num;

	while (try_cnt++ < RCB_RESET_TRY_TIMES) {
		usleep_range(100, 200);
		tx_fbd_num = dsaf_read_dev(q, RCB_RING_TX_RING_FBDNUM_REG);
		if (tx_fbd_num)
			continue;

		dsaf_write_dev(q, RCB_RING_PREFETCH_EN_REG, 0);

		dsaf_write_dev(q, RCB_RING_T0_BE_RST, 1);

		msleep(20);
		could_ret = dsaf_read_dev(q, RCB_RING_COULD_BE_RST);

		wait_cnt = 0;
		while (!could_ret && (wait_cnt < RCB_RESET_WAIT_TIMES)) {
			dsaf_write_dev(q, RCB_RING_T0_BE_RST, 0);

			dsaf_write_dev(q, RCB_RING_T0_BE_RST, 1);

			msleep(20);
			could_ret = dsaf_read_dev(q, RCB_RING_COULD_BE_RST);

			wait_cnt++;
		}

		dsaf_write_dev(q, RCB_RING_T0_BE_RST, 0);

		if (could_ret)
			break;
	}

	if (try_cnt >= RCB_RESET_TRY_TIMES)
		dev_err(q->dev->dev, "port%d reset ring fail\n",
			hns_ae_get_vf_cb(q->handle)->port_index);
}
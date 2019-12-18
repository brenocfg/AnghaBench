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
typedef  int u32 ;
struct hnae_queue {int dummy; } ;

/* Variables and functions */
 int RCB_INT_FLAG_RX ; 
 int RCB_INT_FLAG_TX ; 
 int /*<<< orphan*/  RCB_RING_INTSTS_RX_OVERTIME_REG ; 
 int /*<<< orphan*/  RCB_RING_INTSTS_RX_RING_REG ; 
 int /*<<< orphan*/  RCB_RING_INTSTS_TX_OVERTIME_REG ; 
 int /*<<< orphan*/  RCB_RING_INTSTS_TX_RING_REG ; 
 int /*<<< orphan*/  dsaf_write_dev (struct hnae_queue*,int /*<<< orphan*/ ,int) ; 

void hns_rcb_int_clr_hw(struct hnae_queue *q, u32 flag)
{
	if (flag & RCB_INT_FLAG_TX) {
		dsaf_write_dev(q, RCB_RING_INTSTS_TX_RING_REG, 1);
		dsaf_write_dev(q, RCB_RING_INTSTS_TX_OVERTIME_REG, 1);
	}

	if (flag & RCB_INT_FLAG_RX) {
		dsaf_write_dev(q, RCB_RING_INTSTS_RX_RING_REG, 1);
		dsaf_write_dev(q, RCB_RING_INTSTS_RX_OVERTIME_REG, 1);
	}
}
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
 int /*<<< orphan*/  RCB_RING_INTMSK_RXWL_REG ; 
 int /*<<< orphan*/  RCB_RING_INTMSK_RX_OVERTIME_REG ; 
 int /*<<< orphan*/  RCB_RING_INTMSK_TXWL_REG ; 
 int /*<<< orphan*/  RCB_RING_INTMSK_TX_OVERTIME_REG ; 
 int /*<<< orphan*/  dsaf_write_dev (struct hnae_queue*,int /*<<< orphan*/ ,int) ; 

void hns_rcb_int_ctrl_hw(struct hnae_queue *q, u32 flag, u32 mask)
{
	u32 int_mask_en = !!mask;

	if (flag & RCB_INT_FLAG_TX) {
		dsaf_write_dev(q, RCB_RING_INTMSK_TXWL_REG, int_mask_en);
		dsaf_write_dev(q, RCB_RING_INTMSK_TX_OVERTIME_REG,
			       int_mask_en);
	}

	if (flag & RCB_INT_FLAG_RX) {
		dsaf_write_dev(q, RCB_RING_INTMSK_RXWL_REG, int_mask_en);
		dsaf_write_dev(q, RCB_RING_INTMSK_RX_OVERTIME_REG,
			       int_mask_en);
	}
}
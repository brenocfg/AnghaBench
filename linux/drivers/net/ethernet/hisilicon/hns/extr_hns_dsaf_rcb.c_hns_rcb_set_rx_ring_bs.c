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
typedef  int /*<<< orphan*/  u32 ;
struct hnae_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCB_RING_RX_RING_BD_LEN_REG ; 
 int /*<<< orphan*/  dsaf_write_dev (struct hnae_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_rcb_buf_size2type (int /*<<< orphan*/ ) ; 

void hns_rcb_set_rx_ring_bs(struct hnae_queue *q, u32 buf_size)
{
	u32 bd_size_type = hns_rcb_buf_size2type(buf_size);

	dsaf_write_dev(q, RCB_RING_RX_RING_BD_LEN_REG,
		       bd_size_type);
}
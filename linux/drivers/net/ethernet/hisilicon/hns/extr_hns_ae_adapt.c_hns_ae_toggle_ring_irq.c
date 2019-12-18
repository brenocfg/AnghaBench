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
struct hnae_ring {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCB_INT_FLAG_RX ; 
 int /*<<< orphan*/  RCB_INT_FLAG_TX ; 
 int /*<<< orphan*/  hns_rcb_int_ctrl_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_tx_ring (struct hnae_ring*) ; 

__attribute__((used)) static void hns_ae_toggle_ring_irq(struct hnae_ring *ring, u32 mask)
{
	u32 flag;

	if (is_tx_ring(ring))
		flag = RCB_INT_FLAG_TX;
	else
		flag = RCB_INT_FLAG_RX;

	hns_rcb_int_ctrl_hw(ring->q, flag, mask);
}
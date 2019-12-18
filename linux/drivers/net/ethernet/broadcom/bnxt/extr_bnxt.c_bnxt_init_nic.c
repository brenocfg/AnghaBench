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
struct bnxt {int dummy; } ;

/* Variables and functions */
 int bnxt_init_chip (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_init_cp_rings (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_init_ring_grps (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_init_rx_rings (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_init_tx_rings (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_init_vnics (struct bnxt*) ; 

__attribute__((used)) static int bnxt_init_nic(struct bnxt *bp, bool irq_re_init)
{
	bnxt_init_cp_rings(bp);
	bnxt_init_rx_rings(bp);
	bnxt_init_tx_rings(bp);
	bnxt_init_ring_grps(bp, irq_re_init);
	bnxt_init_vnics(bp);

	return bnxt_init_chip(bp, irq_re_init);
}
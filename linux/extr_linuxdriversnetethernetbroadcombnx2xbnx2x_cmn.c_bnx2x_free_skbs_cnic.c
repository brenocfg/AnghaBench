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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_free_rx_skbs_cnic (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_free_tx_skbs_cnic (struct bnx2x*) ; 

__attribute__((used)) static void bnx2x_free_skbs_cnic(struct bnx2x *bp)
{
	bnx2x_free_tx_skbs_cnic(bp);
	bnx2x_free_rx_skbs_cnic(bp);
}
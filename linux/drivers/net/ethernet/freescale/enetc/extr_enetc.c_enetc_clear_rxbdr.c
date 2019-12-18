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
struct enetc_hw {int dummy; } ;
struct enetc_bdr {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_RBMR ; 
 int /*<<< orphan*/  enetc_rxbdr_wr (struct enetc_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_clear_rxbdr(struct enetc_hw *hw, struct enetc_bdr *rx_ring)
{
	int idx = rx_ring->index;

	/* disable EN bit on ring */
	enetc_rxbdr_wr(hw, idx, ENETC_RBMR, 0);
}
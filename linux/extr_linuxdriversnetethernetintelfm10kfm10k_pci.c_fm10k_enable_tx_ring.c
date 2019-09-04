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
typedef  int u32 ;
struct fm10k_ring {int /*<<< orphan*/  reg_idx; } ;
struct fm10k_hw {int dummy; } ;
struct fm10k_intfc {int /*<<< orphan*/  netdev; struct fm10k_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_TXDCTL (int /*<<< orphan*/ ) ; 
 int FM10K_TXDCTL_ENABLE ; 
 int /*<<< orphan*/  drv ; 
 int fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct fm10k_intfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void fm10k_enable_tx_ring(struct fm10k_intfc *interface,
				 struct fm10k_ring *ring)
{
	struct fm10k_hw *hw = &interface->hw;
	int wait_loop = 10;
	u32 txdctl;
	u8 reg_idx = ring->reg_idx;

	/* if we are already enabled just exit */
	if (fm10k_read_reg(hw, FM10K_TXDCTL(reg_idx)) & FM10K_TXDCTL_ENABLE)
		return;

	/* poll to verify queue is enabled */
	do {
		usleep_range(1000, 2000);
		txdctl = fm10k_read_reg(hw, FM10K_TXDCTL(reg_idx));
	} while (!(txdctl & FM10K_TXDCTL_ENABLE) && --wait_loop);
	if (!wait_loop)
		netif_err(interface, drv, interface->netdev,
			  "Could not enable Tx Queue %d\n", reg_idx);
}
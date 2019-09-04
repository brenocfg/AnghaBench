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
struct fm10k_mbx_info {scalar_t__ mbx_lock; scalar_t__ mbx_hdr; int /*<<< orphan*/  mbx_reg; int /*<<< orphan*/  mbmem_reg; } ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fm10k_mbx_write(struct fm10k_hw *hw, struct fm10k_mbx_info *mbx)
{
	u32 mbmem = mbx->mbmem_reg;

	/* write new msg header to notify recipient of change */
	fm10k_write_reg(hw, mbmem, mbx->mbx_hdr);

	/* write mailbox to send interrupt */
	if (mbx->mbx_lock)
		fm10k_write_reg(hw, mbx->mbx_reg, mbx->mbx_lock);

	/* we no longer are using the header so free it */
	mbx->mbx_hdr = 0;
	mbx->mbx_lock = 0;
}
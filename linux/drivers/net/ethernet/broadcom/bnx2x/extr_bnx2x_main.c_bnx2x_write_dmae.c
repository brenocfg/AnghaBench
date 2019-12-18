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
struct dmae_command {int dst_addr_lo; int len; scalar_t__ dst_addr_hi; int /*<<< orphan*/  src_addr_hi; int /*<<< orphan*/  src_addr_lo; } ;
struct bnx2x {int /*<<< orphan*/  dmae_ready; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  DMAE_DST_GRC ; 
 int /*<<< orphan*/  DMAE_SRC_PCI ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_ind_wr (struct bnx2x*,int,int*,int) ; 
 int /*<<< orphan*/  bnx2x_init_str_wr (struct bnx2x*,int,int*,int) ; 
 int bnx2x_issue_dmae_with_comp (struct bnx2x*,struct dmae_command*,int*) ; 
 int /*<<< orphan*/  bnx2x_panic () ; 
 int /*<<< orphan*/  bnx2x_prep_dmae_with_comp (struct bnx2x*,struct dmae_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* bnx2x_sp (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_comp ; 
 int /*<<< orphan*/ * wb_data ; 

void bnx2x_write_dmae(struct bnx2x *bp, dma_addr_t dma_addr, u32 dst_addr,
		      u32 len32)
{
	int rc;
	struct dmae_command dmae;

	if (!bp->dmae_ready) {
		u32 *data = bnx2x_sp(bp, wb_data[0]);

		if (CHIP_IS_E1(bp))
			bnx2x_init_ind_wr(bp, dst_addr, data, len32);
		else
			bnx2x_init_str_wr(bp, dst_addr, data, len32);
		return;
	}

	/* set opcode and fixed command fields */
	bnx2x_prep_dmae_with_comp(bp, &dmae, DMAE_SRC_PCI, DMAE_DST_GRC);

	/* fill in addresses and len */
	dmae.src_addr_lo = U64_LO(dma_addr);
	dmae.src_addr_hi = U64_HI(dma_addr);
	dmae.dst_addr_lo = dst_addr >> 2;
	dmae.dst_addr_hi = 0;
	dmae.len = len32;

	/* issue the command and wait for completion */
	rc = bnx2x_issue_dmae_with_comp(bp, &dmae, bnx2x_sp(bp, wb_comp));
	if (rc) {
		BNX2X_ERR("DMAE returned failure %d\n", rc);
#ifdef BNX2X_STOP_ON_ERROR
		bnx2x_panic();
#endif
	}
}
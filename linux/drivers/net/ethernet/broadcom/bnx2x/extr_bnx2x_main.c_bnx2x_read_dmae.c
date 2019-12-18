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
struct dmae_command {int src_addr_lo; int len; int /*<<< orphan*/  dst_addr_hi; int /*<<< orphan*/  dst_addr_lo; scalar_t__ src_addr_hi; } ;
struct bnx2x {int /*<<< orphan*/  dmae_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  DMAE_DST_PCI ; 
 int /*<<< orphan*/  DMAE_SRC_GRC ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int bnx2x_issue_dmae_with_comp (struct bnx2x*,struct dmae_command*,int*) ; 
 int /*<<< orphan*/  bnx2x_panic () ; 
 int /*<<< orphan*/  bnx2x_prep_dmae_with_comp (struct bnx2x*,struct dmae_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnx2x_reg_rd_ind (struct bnx2x*,int) ; 
 int* bnx2x_sp (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sp_mapping (struct bnx2x*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_comp ; 
 int /*<<< orphan*/ * wb_data ; 

void bnx2x_read_dmae(struct bnx2x *bp, u32 src_addr, u32 len32)
{
	int rc;
	struct dmae_command dmae;

	if (!bp->dmae_ready) {
		u32 *data = bnx2x_sp(bp, wb_data[0]);
		int i;

		if (CHIP_IS_E1(bp))
			for (i = 0; i < len32; i++)
				data[i] = bnx2x_reg_rd_ind(bp, src_addr + i*4);
		else
			for (i = 0; i < len32; i++)
				data[i] = REG_RD(bp, src_addr + i*4);

		return;
	}

	/* set opcode and fixed command fields */
	bnx2x_prep_dmae_with_comp(bp, &dmae, DMAE_SRC_GRC, DMAE_DST_PCI);

	/* fill in addresses and len */
	dmae.src_addr_lo = src_addr >> 2;
	dmae.src_addr_hi = 0;
	dmae.dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, wb_data));
	dmae.dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, wb_data));
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
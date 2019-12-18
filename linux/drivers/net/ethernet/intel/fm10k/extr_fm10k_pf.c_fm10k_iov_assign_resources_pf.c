#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int total_vfs; int num_vfs; int num_pools; } ;
struct TYPE_3__ {int default_vid; } ;
struct fm10k_hw {TYPE_2__ iov; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int /*<<< orphan*/  FM10K_ITR2 (int) ; 
 int FM10K_ITR_REG_COUNT ; 
 int FM10K_ITR_REG_COUNT_PF ; 
 int FM10K_MAX_QUEUES_PF ; 
 int /*<<< orphan*/  FM10K_MBMEM (int) ; 
 int /*<<< orphan*/  FM10K_PFVFLREC (int) ; 
 int /*<<< orphan*/  FM10K_RQMAP (int) ; 
 int /*<<< orphan*/  FM10K_RXDCTL (int) ; 
 int FM10K_RXDCTL_DROP_ON_EMPTY ; 
 int FM10K_RXDCTL_WRITE_BACK_MIN_DELAY ; 
 int /*<<< orphan*/  FM10K_RXQCTL (int) ; 
 int FM10K_RXQCTL_PF ; 
 int FM10K_RXQCTL_VF ; 
 int FM10K_RXQCTL_VF_SHIFT ; 
 int /*<<< orphan*/  FM10K_TC_CREDIT (int) ; 
 int FM10K_TC_CREDIT_CREDIT_MASK ; 
 int /*<<< orphan*/  FM10K_TC_MAXCREDIT (int) ; 
 int /*<<< orphan*/  FM10K_TC_RATE (int) ; 
 int /*<<< orphan*/  FM10K_TQMAP (int) ; 
 int FM10K_TQMAP_TABLE_SIZE ; 
 int /*<<< orphan*/  FM10K_TXDCTL (int) ; 
 int /*<<< orphan*/  FM10K_TXQCTL (int) ; 
 int FM10K_TXQCTL_PF ; 
 int FM10K_TXQCTL_TC_SHIFT ; 
 int FM10K_TXQCTL_UNLIMITED_BW ; 
 int FM10K_TXQCTL_VF ; 
 int FM10K_TXQCTL_VID_SHIFT ; 
 int FM10K_VFMBMEM_LEN ; 
 int fm10k_queues_per_pool (struct fm10k_hw*) ; 
 int fm10k_vectors_per_pool (struct fm10k_hw*) ; 
 int fm10k_vf_queue_index (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int fm10k_vf_vector_index (struct fm10k_hw*,int) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 fm10k_iov_assign_resources_pf(struct fm10k_hw *hw, u16 num_vfs,
					 u16 num_pools)
{
	u16 qmap_stride, qpp, vpp, vf_q_idx, vf_q_idx0, qmap_idx;
	u32 vid = hw->mac.default_vid << FM10K_TXQCTL_VID_SHIFT;
	int i, j;

	/* hardware only supports up to 64 pools */
	if (num_pools > 64)
		return FM10K_ERR_PARAM;

	/* the number of VFs cannot exceed the number of pools */
	if ((num_vfs > num_pools) || (num_vfs > hw->iov.total_vfs))
		return FM10K_ERR_PARAM;

	/* record number of virtualization entities */
	hw->iov.num_vfs = num_vfs;
	hw->iov.num_pools = num_pools;

	/* determine qmap offsets and counts */
	qmap_stride = (num_vfs > 8) ? 32 : 256;
	qpp = fm10k_queues_per_pool(hw);
	vpp = fm10k_vectors_per_pool(hw);

	/* calculate starting index for queues */
	vf_q_idx = fm10k_vf_queue_index(hw, 0);
	qmap_idx = 0;

	/* establish TCs with -1 credits and no quanta to prevent transmit */
	for (i = 0; i < num_vfs; i++) {
		fm10k_write_reg(hw, FM10K_TC_MAXCREDIT(i), 0);
		fm10k_write_reg(hw, FM10K_TC_RATE(i), 0);
		fm10k_write_reg(hw, FM10K_TC_CREDIT(i),
				FM10K_TC_CREDIT_CREDIT_MASK);
	}

	/* zero out all mbmem registers */
	for (i = FM10K_VFMBMEM_LEN * num_vfs; i--;)
		fm10k_write_reg(hw, FM10K_MBMEM(i), 0);

	/* clear event notification of VF FLR */
	fm10k_write_reg(hw, FM10K_PFVFLREC(0), ~0);
	fm10k_write_reg(hw, FM10K_PFVFLREC(1), ~0);

	/* loop through unallocated rings assigning them back to PF */
	for (i = FM10K_MAX_QUEUES_PF; i < vf_q_idx; i++) {
		fm10k_write_reg(hw, FM10K_TXDCTL(i), 0);
		fm10k_write_reg(hw, FM10K_TXQCTL(i), FM10K_TXQCTL_PF |
				FM10K_TXQCTL_UNLIMITED_BW | vid);
		fm10k_write_reg(hw, FM10K_RXQCTL(i), FM10K_RXQCTL_PF);
	}

	/* PF should have already updated VFITR2[0] */

	/* update all ITR registers to flow to VFITR2[0] */
	for (i = FM10K_ITR_REG_COUNT_PF + 1; i < FM10K_ITR_REG_COUNT; i++) {
		if (!(i & (vpp - 1)))
			fm10k_write_reg(hw, FM10K_ITR2(i), i - vpp);
		else
			fm10k_write_reg(hw, FM10K_ITR2(i), i - 1);
	}

	/* update PF ITR2[0] to reference the last vector */
	fm10k_write_reg(hw, FM10K_ITR2(0),
			fm10k_vf_vector_index(hw, num_vfs - 1));

	/* loop through rings populating rings and TCs */
	for (i = 0; i < num_vfs; i++) {
		/* record index for VF queue 0 for use in end of loop */
		vf_q_idx0 = vf_q_idx;

		for (j = 0; j < qpp; j++, qmap_idx++, vf_q_idx++) {
			/* assign VF and locked TC to queues */
			fm10k_write_reg(hw, FM10K_TXDCTL(vf_q_idx), 0);
			fm10k_write_reg(hw, FM10K_TXQCTL(vf_q_idx),
					(i << FM10K_TXQCTL_TC_SHIFT) | i |
					FM10K_TXQCTL_VF | vid);
			fm10k_write_reg(hw, FM10K_RXDCTL(vf_q_idx),
					FM10K_RXDCTL_WRITE_BACK_MIN_DELAY |
					FM10K_RXDCTL_DROP_ON_EMPTY);
			fm10k_write_reg(hw, FM10K_RXQCTL(vf_q_idx),
					(i << FM10K_RXQCTL_VF_SHIFT) |
					FM10K_RXQCTL_VF);

			/* map queue pair to VF */
			fm10k_write_reg(hw, FM10K_TQMAP(qmap_idx), vf_q_idx);
			fm10k_write_reg(hw, FM10K_RQMAP(qmap_idx), vf_q_idx);
		}

		/* repeat the first ring for all of the remaining VF rings */
		for (; j < qmap_stride; j++, qmap_idx++) {
			fm10k_write_reg(hw, FM10K_TQMAP(qmap_idx), vf_q_idx0);
			fm10k_write_reg(hw, FM10K_RQMAP(qmap_idx), vf_q_idx0);
		}
	}

	/* loop through remaining indexes assigning all to queue 0 */
	while (qmap_idx < FM10K_TQMAP_TABLE_SIZE) {
		fm10k_write_reg(hw, FM10K_TQMAP(qmap_idx), 0);
		fm10k_write_reg(hw, FM10K_RQMAP(qmap_idx), 0);
		qmap_idx++;
	}

	return 0;
}
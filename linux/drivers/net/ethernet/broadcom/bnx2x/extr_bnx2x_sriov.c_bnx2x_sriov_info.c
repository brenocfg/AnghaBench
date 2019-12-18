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
struct bnx2x_sriov {int first_vf_in_pf; int /*<<< orphan*/  pgsz; int /*<<< orphan*/  stride; int /*<<< orphan*/  offset; int /*<<< orphan*/  nr_virtfn; int /*<<< orphan*/  initial; int /*<<< orphan*/  total; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  cap; scalar_t__ nres; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_MAX_NUM_OF_VFS ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  BP_FUNC (struct bnx2x*) ; 
 int BP_PATH (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 scalar_t__ GRC_CONFIG_REG_PF_INIT_VF ; 
 int GRC_CR_PF_INIT_VF_PF_FIRST_VF_NUM_MASK ; 
 scalar_t__ PCICFG_OFFSET ; 
 int REG_RD (struct bnx2x*,scalar_t__) ; 
 scalar_t__ bnx2x_sriov_pci_cfg_info (struct bnx2x*,struct bnx2x_sriov*) ; 

__attribute__((used)) static int bnx2x_sriov_info(struct bnx2x *bp, struct bnx2x_sriov *iov)
{
	u32 val;

	/* read the SRIOV capability structure
	 * The fields can be read via configuration read or
	 * directly from the device (starting at offset PCICFG_OFFSET)
	 */
	if (bnx2x_sriov_pci_cfg_info(bp, iov))
		return -ENODEV;

	/* get the number of SRIOV bars */
	iov->nres = 0;

	/* read the first_vfid */
	val = REG_RD(bp, PCICFG_OFFSET + GRC_CONFIG_REG_PF_INIT_VF);
	iov->first_vf_in_pf = ((val & GRC_CR_PF_INIT_VF_PF_FIRST_VF_NUM_MASK)
			       * 8) - (BNX2X_MAX_NUM_OF_VFS * BP_PATH(bp));

	DP(BNX2X_MSG_IOV,
	   "IOV info[%d]: first vf %d, nres %d, cap 0x%x, ctrl 0x%x, total %d, initial %d, num vfs %d, offset %d, stride %d, page size 0x%x\n",
	   BP_FUNC(bp),
	   iov->first_vf_in_pf, iov->nres, iov->cap, iov->ctrl, iov->total,
	   iov->initial, iov->nr_virtfn, iov->offset, iov->stride, iov->pgsz);

	return 0;
}
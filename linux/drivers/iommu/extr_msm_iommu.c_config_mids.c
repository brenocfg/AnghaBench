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
struct msm_iommu_dev {int /*<<< orphan*/  base; } ;
struct msm_iommu_ctx_dev {int num_mids; int* mids; int num; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_CBACR_N (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_CBNDX (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SET_CBVMID (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_CONTEXTIDR_ASID (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SET_M2VCBR_N (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NSCFG (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SET_VMID (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void config_mids(struct msm_iommu_dev *iommu,
			struct msm_iommu_ctx_dev *master)
{
	int mid, ctx, i;

	for (i = 0; i < master->num_mids; i++) {
		mid = master->mids[i];
		ctx = master->num;

		SET_M2VCBR_N(iommu->base, mid, 0);
		SET_CBACR_N(iommu->base, ctx, 0);

		/* Set VMID = 0 */
		SET_VMID(iommu->base, mid, 0);

		/* Set the context number for that MID to this context */
		SET_CBNDX(iommu->base, mid, ctx);

		/* Set MID associated with this context bank to 0*/
		SET_CBVMID(iommu->base, ctx, 0);

		/* Set the ASID for TLB tagging for this context */
		SET_CONTEXTIDR_ASID(iommu->base, ctx, ctx);

		/* Set security bit override to be Non-secure */
		SET_NSCFG(iommu->base, mid, 3);
	}
}
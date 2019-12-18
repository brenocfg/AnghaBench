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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_BIF_MGCG ; 
 int /*<<< orphan*/  NBIF_MGCG_CTRL_LCLK__NBIF_MGCG_EN_LCLK_MASK ; 
 int /*<<< orphan*/  RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSHUB_MMREG_DIRECT_SYSHUB_MGCG_CTRL_SHUBCLK__SYSHUB_MGCG_EN_SHUBCLK_MASK ; 
 int /*<<< orphan*/  SYSHUB_MMREG_DIRECT_SYSHUB_MGCG_CTRL_SOCCLK__SYSHUB_MGCG_EN_SOCCLK_MASK ; 
 int /*<<< orphan*/  WREG32_PCIE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SHUBCLK ; 
 int /*<<< orphan*/  ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SOCCLK ; 
 int /*<<< orphan*/  nbio_7_0_read_syshub_ind_mmr (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbio_7_0_write_syshub_ind_mmr (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smnNBIF_MGCG_CTRL_LCLK ; 

__attribute__((used)) static void nbio_v7_0_update_medium_grain_clock_gating(struct amdgpu_device *adev,
						       bool enable)
{
	uint32_t def, data;

	/* NBIF_MGCG_CTRL_LCLK */
	def = data = RREG32_PCIE(smnNBIF_MGCG_CTRL_LCLK);

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_BIF_MGCG))
		data |= NBIF_MGCG_CTRL_LCLK__NBIF_MGCG_EN_LCLK_MASK;
	else
		data &= ~NBIF_MGCG_CTRL_LCLK__NBIF_MGCG_EN_LCLK_MASK;

	if (def != data)
		WREG32_PCIE(smnNBIF_MGCG_CTRL_LCLK, data);

	/* SYSHUB_MGCG_CTRL_SOCCLK */
	def = data = nbio_7_0_read_syshub_ind_mmr(adev, ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SOCCLK);

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_BIF_MGCG))
		data |= SYSHUB_MMREG_DIRECT_SYSHUB_MGCG_CTRL_SOCCLK__SYSHUB_MGCG_EN_SOCCLK_MASK;
	else
		data &= ~SYSHUB_MMREG_DIRECT_SYSHUB_MGCG_CTRL_SOCCLK__SYSHUB_MGCG_EN_SOCCLK_MASK;

	if (def != data)
		nbio_7_0_write_syshub_ind_mmr(adev, ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SOCCLK, data);

	/* SYSHUB_MGCG_CTRL_SHUBCLK */
	def = data = nbio_7_0_read_syshub_ind_mmr(adev, ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SHUBCLK);

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_BIF_MGCG))
		data |= SYSHUB_MMREG_DIRECT_SYSHUB_MGCG_CTRL_SHUBCLK__SYSHUB_MGCG_EN_SHUBCLK_MASK;
	else
		data &= ~SYSHUB_MMREG_DIRECT_SYSHUB_MGCG_CTRL_SHUBCLK__SYSHUB_MGCG_EN_SHUBCLK_MASK;

	if (def != data)
		nbio_7_0_write_syshub_ind_mmr(adev, ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SHUBCLK, data);
}
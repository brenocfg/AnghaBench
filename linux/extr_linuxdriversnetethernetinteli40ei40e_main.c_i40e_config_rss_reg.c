#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct i40e_vsi {scalar_t__ vf_id; scalar_t__ type; struct i40e_pf* back; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {TYPE_1__* pdev; struct i40e_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ I40E_HLUT_ARRAY_SIZE ; 
 int /*<<< orphan*/  I40E_PFQF_HKEY (size_t) ; 
 size_t I40E_PFQF_HKEY_MAX_INDEX ; 
 int /*<<< orphan*/  I40E_PFQF_HLUT (size_t) ; 
 size_t I40E_PFQF_HLUT_MAX_INDEX ; 
 int /*<<< orphan*/  I40E_VFQF_HKEY1 (size_t,scalar_t__) ; 
 size_t I40E_VFQF_HKEY1_MAX_INDEX ; 
 int /*<<< orphan*/  I40E_VFQF_HLUT1 (size_t,scalar_t__) ; 
 size_t I40E_VFQF_HLUT_MAX_INDEX ; 
 scalar_t__ I40E_VF_HLUT_ARRAY_SIZE ; 
 scalar_t__ I40E_VSI_MAIN ; 
 scalar_t__ I40E_VSI_SRIOV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_config_rss_reg(struct i40e_vsi *vsi, const u8 *seed,
			       const u8 *lut, u16 lut_size)
{
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	u16 vf_id = vsi->vf_id;
	u8 i;

	/* Fill out hash function seed */
	if (seed) {
		u32 *seed_dw = (u32 *)seed;

		if (vsi->type == I40E_VSI_MAIN) {
			for (i = 0; i <= I40E_PFQF_HKEY_MAX_INDEX; i++)
				wr32(hw, I40E_PFQF_HKEY(i), seed_dw[i]);
		} else if (vsi->type == I40E_VSI_SRIOV) {
			for (i = 0; i <= I40E_VFQF_HKEY1_MAX_INDEX; i++)
				wr32(hw, I40E_VFQF_HKEY1(i, vf_id), seed_dw[i]);
		} else {
			dev_err(&pf->pdev->dev, "Cannot set RSS seed - invalid VSI type\n");
		}
	}

	if (lut) {
		u32 *lut_dw = (u32 *)lut;

		if (vsi->type == I40E_VSI_MAIN) {
			if (lut_size != I40E_HLUT_ARRAY_SIZE)
				return -EINVAL;
			for (i = 0; i <= I40E_PFQF_HLUT_MAX_INDEX; i++)
				wr32(hw, I40E_PFQF_HLUT(i), lut_dw[i]);
		} else if (vsi->type == I40E_VSI_SRIOV) {
			if (lut_size != I40E_VF_HLUT_ARRAY_SIZE)
				return -EINVAL;
			for (i = 0; i <= I40E_VFQF_HLUT_MAX_INDEX; i++)
				wr32(hw, I40E_VFQF_HLUT1(i, vf_id), lut_dw[i]);
		} else {
			dev_err(&pf->pdev->dev, "Cannot set RSS LUT - invalid VSI type\n");
		}
	}
	i40e_flush(hw);

	return 0;
}
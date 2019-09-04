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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t I40E_HLUT_ARRAY_SIZE ; 
 int /*<<< orphan*/  I40E_PFQF_HKEY (size_t) ; 
 size_t I40E_PFQF_HKEY_MAX_INDEX ; 
 int /*<<< orphan*/  I40E_PFQF_HLUT (size_t) ; 
 size_t I40E_PFQF_HLUT_MAX_INDEX ; 
 int /*<<< orphan*/  i40e_read_rx_ctl (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_get_rss_reg(struct i40e_vsi *vsi, u8 *seed,
			    u8 *lut, u16 lut_size)
{
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	u16 i;

	if (seed) {
		u32 *seed_dw = (u32 *)seed;

		for (i = 0; i <= I40E_PFQF_HKEY_MAX_INDEX; i++)
			seed_dw[i] = i40e_read_rx_ctl(hw, I40E_PFQF_HKEY(i));
	}
	if (lut) {
		u32 *lut_dw = (u32 *)lut;

		if (lut_size != I40E_HLUT_ARRAY_SIZE)
			return -EINVAL;
		for (i = 0; i <= I40E_PFQF_HLUT_MAX_INDEX; i++)
			lut_dw[i] = rd32(hw, I40E_PFQF_HLUT(i));
	}

	return 0;
}
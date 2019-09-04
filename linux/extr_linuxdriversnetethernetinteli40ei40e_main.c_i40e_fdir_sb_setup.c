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
struct i40e_vsi {int dummy; } ;
struct i40e_pf {int flags; size_t lan_vsi; TYPE_2__* pdev; TYPE_1__** vsi; int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  seid; } ;

/* Variables and functions */
 int I40E_FLAG_FD_SB_ENABLED ; 
 int I40E_FLAG_FD_SB_INACTIVE ; 
 int /*<<< orphan*/  I40E_GLQF_HKEY (int) ; 
 int I40E_GLQF_HKEY_MAX_INDEX ; 
 int /*<<< orphan*/  I40E_VSI_FDIR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_fdir_clean_ring ; 
 struct i40e_vsi* i40e_find_vsi_by_type (struct i40e_pf*,int /*<<< orphan*/ ) ; 
 struct i40e_vsi* i40e_vsi_setup (struct i40e_pf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_vsi_setup_irqhandler (struct i40e_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void i40e_fdir_sb_setup(struct i40e_pf *pf)
{
	struct i40e_vsi *vsi;

	/* quick workaround for an NVM issue that leaves a critical register
	 * uninitialized
	 */
	if (!rd32(&pf->hw, I40E_GLQF_HKEY(0))) {
		static const u32 hkey[] = {
			0xe640d33f, 0xcdfe98ab, 0x73fa7161, 0x0d7a7d36,
			0xeacb7d61, 0xaa4f05b6, 0x9c5c89ed, 0xfc425ddb,
			0xa4654832, 0xfc7461d4, 0x8f827619, 0xf5c63c21,
			0x95b3a76d};
		int i;

		for (i = 0; i <= I40E_GLQF_HKEY_MAX_INDEX; i++)
			wr32(&pf->hw, I40E_GLQF_HKEY(i), hkey[i]);
	}

	if (!(pf->flags & I40E_FLAG_FD_SB_ENABLED))
		return;

	/* find existing VSI and see if it needs configuring */
	vsi = i40e_find_vsi_by_type(pf, I40E_VSI_FDIR);

	/* create a new VSI if none exists */
	if (!vsi) {
		vsi = i40e_vsi_setup(pf, I40E_VSI_FDIR,
				     pf->vsi[pf->lan_vsi]->seid, 0);
		if (!vsi) {
			dev_info(&pf->pdev->dev, "Couldn't create FDir VSI\n");
			pf->flags &= ~I40E_FLAG_FD_SB_ENABLED;
			pf->flags |= I40E_FLAG_FD_SB_INACTIVE;
			return;
		}
	}

	i40e_vsi_setup_irqhandler(vsi, i40e_fdir_clean_ring);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct ice_vf {int vf_id; int spoofchk; int /*<<< orphan*/  vf_caps; int /*<<< orphan*/  vf_sw_id; struct ice_pf* pf; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {int num_alloc_vfs; int /*<<< orphan*/ * state; TYPE_1__* pdev; struct ice_vf* vf; int /*<<< orphan*/  first_sw; int /*<<< orphan*/  oicr_idx; struct ice_hw hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLINT_DYN_CTL (int /*<<< orphan*/ ) ; 
 int GLINT_DYN_CTL_ITR_INDX_S ; 
 int ICE_ITR_NONE ; 
 int /*<<< orphan*/  ICE_VIRTCHNL_VF_CAP_L2 ; 
 int /*<<< orphan*/  __ICE_OICR_INTR_DIS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ice_vf* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_vf*) ; 
 int /*<<< orphan*/  ice_config_res_vfs (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_irq_dynamic_ena (struct ice_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_sriov (TYPE_1__*) ; 
 int pci_enable_sriov (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ice_alloc_vfs(struct ice_pf *pf, u16 num_alloc_vfs)
{
	struct ice_hw *hw = &pf->hw;
	struct ice_vf *vfs;
	int i, ret;

	/* Disable global interrupt 0 so we don't try to handle the VFLR. */
	wr32(hw, GLINT_DYN_CTL(pf->oicr_idx),
	     ICE_ITR_NONE << GLINT_DYN_CTL_ITR_INDX_S);
	set_bit(__ICE_OICR_INTR_DIS, pf->state);
	ice_flush(hw);

	ret = pci_enable_sriov(pf->pdev, num_alloc_vfs);
	if (ret) {
		pf->num_alloc_vfs = 0;
		goto err_unroll_intr;
	}
	/* allocate memory */
	vfs = devm_kcalloc(&pf->pdev->dev, num_alloc_vfs, sizeof(*vfs),
			   GFP_KERNEL);
	if (!vfs) {
		ret = -ENOMEM;
		goto err_pci_disable_sriov;
	}
	pf->vf = vfs;

	/* apply default profile */
	for (i = 0; i < num_alloc_vfs; i++) {
		vfs[i].pf = pf;
		vfs[i].vf_sw_id = pf->first_sw;
		vfs[i].vf_id = i;

		/* assign default capabilities */
		set_bit(ICE_VIRTCHNL_VF_CAP_L2, &vfs[i].vf_caps);
		vfs[i].spoofchk = true;
	}
	pf->num_alloc_vfs = num_alloc_vfs;

	/* VF resources get allocated with initialization */
	if (!ice_config_res_vfs(pf)) {
		ret = -EIO;
		goto err_unroll_sriov;
	}

	return ret;

err_unroll_sriov:
	pf->vf = NULL;
	devm_kfree(&pf->pdev->dev, vfs);
	vfs = NULL;
	pf->num_alloc_vfs = 0;
err_pci_disable_sriov:
	pci_disable_sriov(pf->pdev);
err_unroll_intr:
	/* rearm interrupts here */
	ice_irq_dynamic_ena(hw, NULL, NULL);
	clear_bit(__ICE_OICR_INTR_DIS, pf->state);
	return ret;
}
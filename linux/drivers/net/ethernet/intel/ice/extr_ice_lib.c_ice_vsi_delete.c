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
struct ice_vsi_ctx {int /*<<< orphan*/  info; int /*<<< orphan*/  vsi_num; int /*<<< orphan*/  vf_num; } ;
struct ice_vsi {scalar_t__ type; int /*<<< orphan*/  vsi_num; int /*<<< orphan*/  idx; int /*<<< orphan*/  info; int /*<<< orphan*/  vf_id; struct ice_pf* back; } ;
struct ice_pf {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ICE_VSI_VF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_vsi_ctx*) ; 
 struct ice_vsi_ctx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ice_free_vsi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ice_vsi_ctx*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void ice_vsi_delete(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	struct ice_vsi_ctx *ctxt;
	enum ice_status status;

	ctxt = devm_kzalloc(&pf->pdev->dev, sizeof(*ctxt), GFP_KERNEL);
	if (!ctxt)
		return;

	if (vsi->type == ICE_VSI_VF)
		ctxt->vf_num = vsi->vf_id;
	ctxt->vsi_num = vsi->vsi_num;

	memcpy(&ctxt->info, &vsi->info, sizeof(ctxt->info));

	status = ice_free_vsi(&pf->hw, vsi->idx, ctxt, false, NULL);
	if (status)
		dev_err(&pf->pdev->dev, "Failed to delete VSI %i in FW\n",
			vsi->vsi_num);

	devm_kfree(&pf->pdev->dev, ctxt);
}
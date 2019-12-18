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
struct ice_vsi {size_t idx; struct ice_pf* back; } ;
struct ice_pf {size_t next_vsi; TYPE_1__* pdev; int /*<<< orphan*/  sw_mutex; struct ice_vsi** vsi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_arrays (struct ice_vsi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ice_vsi_clear(struct ice_vsi *vsi)
{
	struct ice_pf *pf = NULL;

	if (!vsi)
		return 0;

	if (!vsi->back)
		return -EINVAL;

	pf = vsi->back;

	if (!pf->vsi[vsi->idx] || pf->vsi[vsi->idx] != vsi) {
		dev_dbg(&pf->pdev->dev, "vsi does not exist at pf->vsi[%d]\n",
			vsi->idx);
		return -EINVAL;
	}

	mutex_lock(&pf->sw_mutex);
	/* updates the PF for this cleared VSI */

	pf->vsi[vsi->idx] = NULL;
	if (vsi->idx < pf->next_vsi)
		pf->next_vsi = vsi->idx;

	ice_vsi_free_arrays(vsi);
	mutex_unlock(&pf->sw_mutex);
	devm_kfree(&pf->pdev->dev, vsi);

	return 0;
}
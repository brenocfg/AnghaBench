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
struct i40e_vsi {size_t idx; int /*<<< orphan*/  af_xdp_zc_qps; int /*<<< orphan*/  base_vector; int /*<<< orphan*/  base_queue; int /*<<< orphan*/  type; struct i40e_pf* back; } ;
struct i40e_pf {size_t next_vsi; int /*<<< orphan*/  switch_mutex; struct i40e_vsi** vsi; int /*<<< orphan*/  irq_pile; int /*<<< orphan*/  qp_pile; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t,size_t,size_t,...) ; 
 int /*<<< orphan*/  i40e_clear_rss_config_user (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_put_lump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  i40e_vsi_free_arrays (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  kfree (struct i40e_vsi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vsi_clear(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf;

	if (!vsi)
		return 0;

	if (!vsi->back)
		goto free_vsi;
	pf = vsi->back;

	mutex_lock(&pf->switch_mutex);
	if (!pf->vsi[vsi->idx]) {
		dev_err(&pf->pdev->dev, "pf->vsi[%d] is NULL, just free vsi[%d](type %d)\n",
			vsi->idx, vsi->idx, vsi->type);
		goto unlock_vsi;
	}

	if (pf->vsi[vsi->idx] != vsi) {
		dev_err(&pf->pdev->dev,
			"pf->vsi[%d](type %d) != vsi[%d](type %d): no free!\n",
			pf->vsi[vsi->idx]->idx,
			pf->vsi[vsi->idx]->type,
			vsi->idx, vsi->type);
		goto unlock_vsi;
	}

	/* updates the PF for this cleared vsi */
	i40e_put_lump(pf->qp_pile, vsi->base_queue, vsi->idx);
	i40e_put_lump(pf->irq_pile, vsi->base_vector, vsi->idx);

	bitmap_free(vsi->af_xdp_zc_qps);
	i40e_vsi_free_arrays(vsi, true);
	i40e_clear_rss_config_user(vsi);

	pf->vsi[vsi->idx] = NULL;
	if (vsi->idx < pf->next_vsi)
		pf->next_vsi = vsi->idx;

unlock_vsi:
	mutex_unlock(&pf->switch_mutex);
free_vsi:
	kfree(vsi);

	return 0;
}
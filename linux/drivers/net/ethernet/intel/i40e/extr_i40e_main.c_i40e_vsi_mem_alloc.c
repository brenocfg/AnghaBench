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
struct i40e_vsi {int type; int idx; int rss_table_size; int netdev_registered; int irqs_ready; int /*<<< orphan*/  af_xdp_zc_qps; int /*<<< orphan*/  mac_filter_hash_lock; int /*<<< orphan*/  mac_filter_hash; int /*<<< orphan*/  work_limit; scalar_t__ int_rate_limit; scalar_t__ flags; int /*<<< orphan*/  state; struct i40e_pf* back; } ;
struct i40e_pf {int next_vsi; int num_alloc_vsi; int rss_table_size; int /*<<< orphan*/  switch_mutex; struct i40e_vsi** vsi; int /*<<< orphan*/  num_lan_qps; } ;
typedef  enum i40e_vsi_type { ____Placeholder_i40e_vsi_type } i40e_vsi_type ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I40E_DEFAULT_IRQ_WORK ; 
 scalar_t__ I40E_VSI_MAIN ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_msix_clean_rings ; 
 int i40e_set_num_rings_in_vsi (struct i40e_vsi*) ; 
 int i40e_vsi_alloc_arrays (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_vsi_setup_irqhandler (struct i40e_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i40e_vsi*) ; 
 struct i40e_vsi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vsi_mem_alloc(struct i40e_pf *pf, enum i40e_vsi_type type)
{
	int ret = -ENODEV;
	struct i40e_vsi *vsi;
	int vsi_idx;
	int i;

	/* Need to protect the allocation of the VSIs at the PF level */
	mutex_lock(&pf->switch_mutex);

	/* VSI list may be fragmented if VSI creation/destruction has
	 * been happening.  We can afford to do a quick scan to look
	 * for any free VSIs in the list.
	 *
	 * find next empty vsi slot, looping back around if necessary
	 */
	i = pf->next_vsi;
	while (i < pf->num_alloc_vsi && pf->vsi[i])
		i++;
	if (i >= pf->num_alloc_vsi) {
		i = 0;
		while (i < pf->next_vsi && pf->vsi[i])
			i++;
	}

	if (i < pf->num_alloc_vsi && !pf->vsi[i]) {
		vsi_idx = i;             /* Found one! */
	} else {
		ret = -ENODEV;
		goto unlock_pf;  /* out of VSI slots! */
	}
	pf->next_vsi = ++i;

	vsi = kzalloc(sizeof(*vsi), GFP_KERNEL);
	if (!vsi) {
		ret = -ENOMEM;
		goto unlock_pf;
	}
	vsi->type = type;
	vsi->back = pf;
	set_bit(__I40E_VSI_DOWN, vsi->state);
	vsi->flags = 0;
	vsi->idx = vsi_idx;
	vsi->int_rate_limit = 0;
	vsi->rss_table_size = (vsi->type == I40E_VSI_MAIN) ?
				pf->rss_table_size : 64;
	vsi->netdev_registered = false;
	vsi->work_limit = I40E_DEFAULT_IRQ_WORK;
	hash_init(vsi->mac_filter_hash);
	vsi->irqs_ready = false;

	if (type == I40E_VSI_MAIN) {
		vsi->af_xdp_zc_qps = bitmap_zalloc(pf->num_lan_qps, GFP_KERNEL);
		if (!vsi->af_xdp_zc_qps)
			goto err_rings;
	}

	ret = i40e_set_num_rings_in_vsi(vsi);
	if (ret)
		goto err_rings;

	ret = i40e_vsi_alloc_arrays(vsi, true);
	if (ret)
		goto err_rings;

	/* Setup default MSIX irq handler for VSI */
	i40e_vsi_setup_irqhandler(vsi, i40e_msix_clean_rings);

	/* Initialize VSI lock */
	spin_lock_init(&vsi->mac_filter_hash_lock);
	pf->vsi[vsi_idx] = vsi;
	ret = vsi_idx;
	goto unlock_pf;

err_rings:
	bitmap_free(vsi->af_xdp_zc_qps);
	pf->next_vsi = i - 1;
	kfree(vsi);
unlock_pf:
	mutex_unlock(&pf->switch_mutex);
	return ret;
}
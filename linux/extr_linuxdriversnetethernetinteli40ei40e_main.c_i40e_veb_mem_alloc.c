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
struct i40e_veb {int idx; int enabled_tc; struct i40e_pf* pf; } ;
struct i40e_pf {int /*<<< orphan*/  switch_mutex; struct i40e_veb** veb; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I40E_MAX_VEB ; 
 struct i40e_veb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_veb_mem_alloc(struct i40e_pf *pf)
{
	int ret = -ENOENT;
	struct i40e_veb *veb;
	int i;

	/* Need to protect the allocation of switch elements at the PF level */
	mutex_lock(&pf->switch_mutex);

	/* VEB list may be fragmented if VEB creation/destruction has
	 * been happening.  We can afford to do a quick scan to look
	 * for any free slots in the list.
	 *
	 * find next empty veb slot, looping back around if necessary
	 */
	i = 0;
	while ((i < I40E_MAX_VEB) && (pf->veb[i] != NULL))
		i++;
	if (i >= I40E_MAX_VEB) {
		ret = -ENOMEM;
		goto err_alloc_veb;  /* out of VEB slots! */
	}

	veb = kzalloc(sizeof(*veb), GFP_KERNEL);
	if (!veb) {
		ret = -ENOMEM;
		goto err_alloc_veb;
	}
	veb->pf = pf;
	veb->idx = i;
	veb->enabled_tc = 1;

	pf->veb[i] = veb;
	ret = i;
err_alloc_veb:
	mutex_unlock(&pf->switch_mutex);
	return ret;
}
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
struct i40e_veb {size_t idx; struct i40e_pf* pf; } ;
struct i40e_pf {int /*<<< orphan*/  switch_mutex; struct i40e_veb** veb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct i40e_veb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40e_veb_clear(struct i40e_veb *veb)
{
	if (!veb)
		return;

	if (veb->pf) {
		struct i40e_pf *pf = veb->pf;

		mutex_lock(&pf->switch_mutex);
		if (pf->veb[veb->idx] == veb)
			pf->veb[veb->idx] = NULL;
		mutex_unlock(&pf->switch_mutex);
	}

	kfree(veb);
}
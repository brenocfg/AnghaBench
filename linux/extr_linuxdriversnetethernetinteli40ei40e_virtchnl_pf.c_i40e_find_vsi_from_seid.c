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
typedef  scalar_t__ u16 ;
struct i40e_vsi {scalar_t__ seid; } ;
struct i40e_vf {int num_tc; TYPE_1__* ch; struct i40e_pf* pf; } ;
struct i40e_pf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsi_id; } ;

/* Variables and functions */
 struct i40e_vsi* i40e_find_vsi_from_id (struct i40e_pf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i40e_vsi *i40e_find_vsi_from_seid(struct i40e_vf *vf, u16 seid)
{
	struct i40e_pf *pf = vf->pf;
	struct i40e_vsi *vsi = NULL;
	int i;

	for (i = 0; i < vf->num_tc ; i++) {
		vsi = i40e_find_vsi_from_id(pf, vf->ch[i].vsi_id);
		if (vsi && vsi->seid == seid)
			return vsi;
	}
	return NULL;
}
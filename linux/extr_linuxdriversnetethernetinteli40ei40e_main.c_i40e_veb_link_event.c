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
struct i40e_veb {scalar_t__ uplink_seid; scalar_t__ seid; struct i40e_pf* pf; } ;
struct i40e_pf {int num_alloc_vsi; TYPE_1__** vsi; struct i40e_veb** veb; } ;
struct TYPE_2__ {scalar_t__ uplink_seid; } ;

/* Variables and functions */
 int I40E_MAX_VEB ; 
 int /*<<< orphan*/  i40e_vsi_link_event (TYPE_1__*,int) ; 

__attribute__((used)) static void i40e_veb_link_event(struct i40e_veb *veb, bool link_up)
{
	struct i40e_pf *pf;
	int i;

	if (!veb || !veb->pf)
		return;
	pf = veb->pf;

	/* depth first... */
	for (i = 0; i < I40E_MAX_VEB; i++)
		if (pf->veb[i] && (pf->veb[i]->uplink_seid == veb->seid))
			i40e_veb_link_event(pf->veb[i], link_up);

	/* ... now the local VSIs */
	for (i = 0; i < pf->num_alloc_vsi; i++)
		if (pf->vsi[i] && (pf->vsi[i]->uplink_seid == veb->seid))
			i40e_vsi_link_event(pf->vsi[i], link_up);
}
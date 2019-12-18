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
typedef  size_t u8 ;
typedef  size_t u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * queue_mapping; int /*<<< orphan*/  mapping_flags; } ;
struct i40e_vsi {TYPE_1__ info; } ;
struct i40e_vf {struct i40e_pf* pf; } ;
struct i40e_pf {int dummy; } ;

/* Variables and functions */
 int I40E_AQ_VSI_QUE_MAP_NONCONTIG ; 
 size_t I40E_QUEUE_END_OF_LIST ; 
 struct i40e_vsi* i40e_find_vsi_from_id (struct i40e_pf*,size_t) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 i40e_vc_get_pf_queue_id(struct i40e_vf *vf, u16 vsi_id,
				   u8 vsi_queue_id)
{
	struct i40e_pf *pf = vf->pf;
	struct i40e_vsi *vsi = i40e_find_vsi_from_id(pf, vsi_id);
	u16 pf_queue_id = I40E_QUEUE_END_OF_LIST;

	if (!vsi)
		return pf_queue_id;

	if (le16_to_cpu(vsi->info.mapping_flags) &
	    I40E_AQ_VSI_QUE_MAP_NONCONTIG)
		pf_queue_id =
			le16_to_cpu(vsi->info.queue_mapping[vsi_queue_id]);
	else
		pf_queue_id = le16_to_cpu(vsi->info.queue_mapping[0]) +
			      vsi_queue_id;

	return pf_queue_id;
}
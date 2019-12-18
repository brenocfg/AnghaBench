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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi {scalar_t__ alloc_txq; } ;
struct ice_vf {int /*<<< orphan*/  pf; } ;

/* Variables and functions */
 struct ice_vsi* ice_find_vsi_from_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ice_vc_isvalid_q_id(struct ice_vf *vf, u16 vsi_id, u8 qid)
{
	struct ice_vsi *vsi = ice_find_vsi_from_id(vf->pf, vsi_id);
	/* allocated Tx and Rx queues should be always equal for VF VSI */
	return (vsi && (qid < vsi->alloc_txq));
}
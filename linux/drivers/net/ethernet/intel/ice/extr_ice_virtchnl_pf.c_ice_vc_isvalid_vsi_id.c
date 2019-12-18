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
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi {scalar_t__ vf_id; } ;
struct ice_vf {scalar_t__ vf_id; struct ice_pf* pf; } ;
struct ice_pf {int dummy; } ;

/* Variables and functions */
 struct ice_vsi* ice_find_vsi_from_id (struct ice_pf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ice_vc_isvalid_vsi_id(struct ice_vf *vf, u16 vsi_id)
{
	struct ice_pf *pf = vf->pf;
	struct ice_vsi *vsi;

	vsi = ice_find_vsi_from_id(pf, vsi_id);

	return (vsi && (vsi->vf_id == vf->vf_id));
}
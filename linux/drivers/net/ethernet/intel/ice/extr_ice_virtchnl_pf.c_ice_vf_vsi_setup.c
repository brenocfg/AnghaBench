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
struct ice_vsi {int dummy; } ;
struct ice_port_info {int dummy; } ;
struct ice_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_VSI_VF ; 
 struct ice_vsi* ice_vsi_setup (struct ice_pf*,struct ice_port_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ice_vsi *
ice_vf_vsi_setup(struct ice_pf *pf, struct ice_port_info *pi, u16 vf_id)
{
	return ice_vsi_setup(pf, pi, ICE_VSI_VF, vf_id);
}
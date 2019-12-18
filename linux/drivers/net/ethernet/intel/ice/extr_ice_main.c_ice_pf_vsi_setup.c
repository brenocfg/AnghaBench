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
struct ice_vsi {int dummy; } ;
struct ice_port_info {int dummy; } ;
struct ice_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_INVAL_VFID ; 
 int /*<<< orphan*/  ICE_VSI_PF ; 
 struct ice_vsi* ice_vsi_setup (struct ice_pf*,struct ice_port_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ice_vsi *
ice_pf_vsi_setup(struct ice_pf *pf, struct ice_port_info *pi)
{
	return ice_vsi_setup(pf, pi, ICE_VSI_PF, ICE_INVAL_VFID);
}
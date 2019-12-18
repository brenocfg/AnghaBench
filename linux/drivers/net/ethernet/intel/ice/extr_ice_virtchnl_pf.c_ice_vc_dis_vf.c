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
struct ice_vf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ice_reset_vf (struct ice_vf*,int) ; 
 int /*<<< orphan*/  ice_vc_notify_vf_reset (struct ice_vf*) ; 

__attribute__((used)) static void ice_vc_dis_vf(struct ice_vf *vf)
{
	ice_vc_notify_vf_reset(vf);
	ice_reset_vf(vf, false);
}
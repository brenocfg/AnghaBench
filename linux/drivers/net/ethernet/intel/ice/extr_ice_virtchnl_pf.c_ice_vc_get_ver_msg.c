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
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_version_info {int /*<<< orphan*/  minor; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct ice_vf {struct virtchnl_version_info vf_ver; } ;

/* Variables and functions */
 scalar_t__ VF_IS_V10 (struct virtchnl_version_info*) ; 
 int /*<<< orphan*/  VIRTCHNL_OP_VERSION ; 
 int /*<<< orphan*/  VIRTCHNL_STATUS_SUCCESS ; 
 int /*<<< orphan*/  VIRTCHNL_VERSION_MAJOR ; 
 int /*<<< orphan*/  VIRTCHNL_VERSION_MINOR ; 
 int /*<<< orphan*/  VIRTCHNL_VERSION_MINOR_NO_VF_CAPS ; 
 int ice_vc_send_msg_to_vf (struct ice_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ice_vc_get_ver_msg(struct ice_vf *vf, u8 *msg)
{
	struct virtchnl_version_info info = {
		VIRTCHNL_VERSION_MAJOR, VIRTCHNL_VERSION_MINOR
	};

	vf->vf_ver = *(struct virtchnl_version_info *)msg;
	/* VFs running the 1.0 API expect to get 1.0 back or they will cry. */
	if (VF_IS_V10(&vf->vf_ver))
		info.minor = VIRTCHNL_VERSION_MINOR_NO_VF_CAPS;

	return ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_VERSION,
				     VIRTCHNL_STATUS_SUCCESS, (u8 *)&info,
				     sizeof(struct virtchnl_version_info));
}
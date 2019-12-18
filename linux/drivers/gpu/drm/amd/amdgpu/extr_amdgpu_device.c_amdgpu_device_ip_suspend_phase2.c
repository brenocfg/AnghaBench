#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pp_handle; TYPE_3__* pp_funcs; } ;
struct amdgpu_device {int num_ip_blocks; TYPE_6__* ip_blocks; int /*<<< orphan*/  mp1_state; TYPE_4__ powerplay; } ;
struct TYPE_11__ {int hw; int /*<<< orphan*/  valid; } ;
struct TYPE_12__ {TYPE_5__ status; TYPE_2__* version; } ;
struct TYPE_9__ {int (* set_mp1_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__ type; TYPE_1__* funcs; } ;
struct TYPE_7__ {int (* suspend ) (struct amdgpu_device*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ AMD_IP_BLOCK_TYPE_DCE ; 
 scalar_t__ AMD_IP_BLOCK_TYPE_SMC ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int stub1 (struct amdgpu_device*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_device_ip_suspend_phase2(struct amdgpu_device *adev)
{
	int i, r;

	for (i = adev->num_ip_blocks - 1; i >= 0; i--) {
		if (!adev->ip_blocks[i].status.valid)
			continue;
		/* displays are handled in phase1 */
		if (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_DCE)
			continue;
		/* XXX handle errors */
		r = adev->ip_blocks[i].version->funcs->suspend(adev);
		/* XXX handle errors */
		if (r) {
			DRM_ERROR("suspend of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
		}
		adev->ip_blocks[i].status.hw = false;
		/* handle putting the SMC in the appropriate state */
		if (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_SMC) {
			if (is_support_sw_smu(adev)) {
				/* todo */
			} else if (adev->powerplay.pp_funcs &&
					   adev->powerplay.pp_funcs->set_mp1_state) {
				r = adev->powerplay.pp_funcs->set_mp1_state(
					adev->powerplay.pp_handle,
					adev->mp1_state);
				if (r) {
					DRM_ERROR("SMC failed to set mp1 state %d, %d\n",
						  adev->mp1_state, r);
					return r;
				}
			}
		}

		adev->ip_blocks[i].status.hw = false;
	}

	return 0;
}
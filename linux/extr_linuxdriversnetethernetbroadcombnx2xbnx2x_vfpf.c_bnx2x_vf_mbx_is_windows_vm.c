#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vf_os; } ;
struct TYPE_3__ {int num_mc_filters; } ;
struct vfpf_acquire_tlv {TYPE_2__ vfdev_info; TYPE_1__ resc_request; int /*<<< orphan*/  bulletin_addr; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int VF_OS_MASK ; 
 int VF_OS_WINDOWS ; 

__attribute__((used)) static bool bnx2x_vf_mbx_is_windows_vm(struct bnx2x *bp,
				       struct vfpf_acquire_tlv *acquire)
{
	/* Windows driver does one of three things:
	 * 1. Old driver doesn't have bulletin board address set.
	 * 2. 'Middle' driver sends mc_num == 32.
	 * 3. New driver sets the OS field.
	 */
	if (!acquire->bulletin_addr ||
	    acquire->resc_request.num_mc_filters == 32 ||
	    ((acquire->vfdev_info.vf_os & VF_OS_MASK) ==
	     VF_OS_WINDOWS))
		return true;

	return false;
}
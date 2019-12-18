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
typedef  int u32 ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_client {scalar_t__ super; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GP100_VMM_VN_FAULT_CANCEL 129 
#define  GP100_VMM_VN_FAULT_REPLAY 128 
 int gp100_vmm_fault_cancel (struct nvkm_vmm*,void*,int) ; 
 int gp100_vmm_fault_replay (struct nvkm_vmm*,void*,int) ; 

int
gp100_vmm_mthd(struct nvkm_vmm *vmm,
	       struct nvkm_client *client, u32 mthd, void *argv, u32 argc)
{
	if (client->super) {
		switch (mthd) {
		case GP100_VMM_VN_FAULT_REPLAY:
			return gp100_vmm_fault_replay(vmm, argv, argc);
		case GP100_VMM_VN_FAULT_CANCEL:
			return gp100_vmm_fault_cancel(vmm, argv, argc);
		default:
			break;
		}
	}
	return -EINVAL;
}
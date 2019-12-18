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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm {int dummy; } ;
struct gp100_vmm_fault_replay_vn {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  gf100_vmm_invalidate (struct nvkm_vmm*,int) ; 
 int nvif_unvers (int,void**,int /*<<< orphan*/ *,struct gp100_vmm_fault_replay_vn) ; 

__attribute__((used)) static int
gp100_vmm_fault_replay(struct nvkm_vmm *vmm, void *argv, u32 argc)
{
	union {
		struct gp100_vmm_fault_replay_vn vn;
	} *args = argv;
	int ret = -ENOSYS;

	if (!(ret = nvif_unvers(ret, &argv, &argc, args->vn))) {
		gf100_vmm_invalidate(vmm, 0x0000000b); /* REPLAY_GLOBAL. */
	}

	return ret;
}
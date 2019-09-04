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
struct TYPE_4__ {int /*<<< orphan*/  se_fuse; int /*<<< orphan*/  ae_fuse; scalar_t__ valid; } ;
union emu_fuse_map {TYPE_2__ s; int /*<<< orphan*/  value; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  se_cores; int /*<<< orphan*/  ae_cores; } ;
struct nitrox_device {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ AE_CORES_PER_CLUSTER ; 
 int /*<<< orphan*/  EMU_FUSE_MAPX (int) ; 
 int NR_CLUSTERS ; 
 scalar_t__ SE_CORES_PER_CLUSTER ; 
 scalar_t__ hweight16 (int /*<<< orphan*/ ) ; 
 scalar_t__ hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_read_csr (struct nitrox_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nitrox_get_hwinfo(struct nitrox_device *ndev)
{
	union emu_fuse_map emu_fuse;
	u64 offset;
	int i;

	for (i = 0; i < NR_CLUSTERS; i++) {
		u8 dead_cores;

		offset = EMU_FUSE_MAPX(i);
		emu_fuse.value = nitrox_read_csr(ndev, offset);
		if (emu_fuse.s.valid) {
			dead_cores = hweight32(emu_fuse.s.ae_fuse);
			ndev->hw.ae_cores += AE_CORES_PER_CLUSTER - dead_cores;
			dead_cores = hweight16(emu_fuse.s.se_fuse);
			ndev->hw.se_cores += SE_CORES_PER_CLUSTER - dead_cores;
		}
	}
}
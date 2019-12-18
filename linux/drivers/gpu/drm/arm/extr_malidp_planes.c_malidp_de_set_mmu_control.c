#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct malidp_plane_state {int /*<<< orphan*/  mmu_prefetch_pgsize; int /*<<< orphan*/  n_planes; int /*<<< orphan*/  mmu_prefetch_mode; } ;
struct malidp_plane {TYPE_1__* layer; int /*<<< orphan*/  hwdev; } ;
struct TYPE_2__ {scalar_t__ mmu_ctrl_offset; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALIDP_MMU_PREFETCH_READAHEAD ; 
 int /*<<< orphan*/  malidp_calc_mmu_control_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void malidp_de_set_mmu_control(struct malidp_plane *mp,
				      struct malidp_plane_state *ms)
{
	u32 mmu_ctrl;

	/* check hardware supports MMU prefetch */
	if (!mp->layer->mmu_ctrl_offset)
		return;

	mmu_ctrl = malidp_calc_mmu_control_value(ms->mmu_prefetch_mode,
						 MALIDP_MMU_PREFETCH_READAHEAD,
						 ms->n_planes,
						 ms->mmu_prefetch_pgsize);

	malidp_hw_write(mp->hwdev, mmu_ctrl,
			mp->layer->base + mp->layer->mmu_ctrl_offset);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  rotation; TYPE_2__* fb; } ;
struct malidp_plane_state {TYPE_3__ base; } ;
typedef  enum mmu_prefetch_mode { ____Placeholder_mmu_prefetch_mode } mmu_prefetch_mode ;
struct TYPE_5__ {int /*<<< orphan*/  modifier; TYPE_1__* format; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int MALIDP_MMU_PREFETCH_FULL_PGSIZES ; 
 int MALIDP_MMU_PREFETCH_PARTIAL_PGSIZES ; 
 int MALIDP_PREFETCH_MODE_FULL ; 
 int MALIDP_PREFETCH_MODE_NONE ; 
 int MALIDP_PREFETCH_MODE_PARTIAL ; 
 int __ffs (int) ; 
 int __fls (int) ; 
 scalar_t__ malidp_check_pages_threshold (struct malidp_plane_state*,int) ; 
 scalar_t__ malidp_partial_prefetch_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum mmu_prefetch_mode malidp_mmu_prefetch_select_mode
		(struct malidp_plane_state *ms,	u32 *pgsize_bitmap)
{
	u32 pgsizes;

	/* get the full-frame prefetch page size(s) supported by the MMU */
	pgsizes = *pgsize_bitmap & MALIDP_MMU_PREFETCH_FULL_PGSIZES;

	while (pgsizes) {
		u32 largest_pgsize = 1 << __fls(pgsizes);

		if (malidp_check_pages_threshold(ms, largest_pgsize)) {
			*pgsize_bitmap = largest_pgsize;
			return MALIDP_PREFETCH_MODE_FULL;
		}

		pgsizes -= largest_pgsize;
	}

	/* get the partial-frame prefetch page size(s) supported by the MMU */
	pgsizes = *pgsize_bitmap & MALIDP_MMU_PREFETCH_PARTIAL_PGSIZES;

	if (malidp_partial_prefetch_supported(ms->base.fb->format->format,
					      ms->base.fb->modifier,
					      ms->base.rotation)) {
		/* partial prefetch using the smallest page size */
		*pgsize_bitmap = 1 << __ffs(pgsizes);
		return MALIDP_PREFETCH_MODE_PARTIAL;
	}
	*pgsize_bitmap = 0;
	return MALIDP_PREFETCH_MODE_NONE;
}
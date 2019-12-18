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
typedef  int u32 ;
struct TYPE_2__ {int idx_mask; } ;
struct cxgbi_ppm {int base_idx; TYPE_1__ tformat; } ;

/* Variables and functions */
 int PPOD_IDX_SHIFT ; 

__attribute__((used)) static inline u32 cxgbi_ppm_ddp_tag_get_idx(struct cxgbi_ppm *ppm,
					    u32 ddp_tag)
{
	u32 hw_idx = (ddp_tag >> PPOD_IDX_SHIFT) &
			ppm->tformat.idx_mask;

	return hw_idx - ppm->base_idx;
}
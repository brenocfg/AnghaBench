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
typedef  size_t u32 ;
struct cxgbi_ppm {TYPE_1__* ppod_data; } ;
struct TYPE_2__ {unsigned long caller_data; } ;

/* Variables and functions */
 size_t cxgbi_ppm_ddp_tag_get_idx (struct cxgbi_ppm*,size_t) ; 

__attribute__((used)) static inline unsigned long
cxgbi_ppm_get_tag_caller_data(struct cxgbi_ppm *ppm,
			      u32 ddp_tag)
{
	u32 idx = cxgbi_ppm_ddp_tag_get_idx(ppm, ddp_tag);

	return ppm->ppod_data[idx].caller_data;
}
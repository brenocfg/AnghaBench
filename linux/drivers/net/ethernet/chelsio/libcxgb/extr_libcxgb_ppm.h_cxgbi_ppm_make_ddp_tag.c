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
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int PPOD_IDX_SHIFT ; 

__attribute__((used)) static inline u32 cxgbi_ppm_make_ddp_tag(unsigned int hw_idx,
					 unsigned char color)
{
	return (hw_idx << PPOD_IDX_SHIFT) | ((u32)color);
}
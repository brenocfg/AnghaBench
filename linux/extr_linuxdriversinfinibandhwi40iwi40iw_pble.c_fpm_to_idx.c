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
typedef  int u64 ;
typedef  int u32 ;
struct i40iw_hmc_pble_rsrc {int fpm_base_addr; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 fpm_to_idx(struct i40iw_hmc_pble_rsrc *pble_rsrc, u64 addr)
{
	return (addr - (pble_rsrc->fpm_base_addr)) >> 3;
}
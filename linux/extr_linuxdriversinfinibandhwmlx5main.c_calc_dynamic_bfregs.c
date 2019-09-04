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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_MAX_DYN_BFREGS ; 
 int /*<<< orphan*/  MLX5_MIN_DYN_BFREGS ; 
 int PAGE_SIZE ; 

__attribute__((used)) static u16 calc_dynamic_bfregs(int uars_per_sys_page)
{
	/* Large page with non 4k uar support might limit the dynamic size */
	if (uars_per_sys_page == 1  && PAGE_SIZE > 4096)
		return MLX5_MIN_DYN_BFREGS;

	return MLX5_MAX_DYN_BFREGS;
}
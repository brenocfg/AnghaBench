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
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int MLX5_MKEY_MASK_LEN ; 
 int MLX5_MKEY_MASK_PAGE_SIZE ; 
 int MLX5_MKEY_MASK_START_ADDR ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 

__attribute__((used)) static __be64 get_umr_update_translation_mask(void)
{
	u64 result;

	result = MLX5_MKEY_MASK_LEN |
		 MLX5_MKEY_MASK_PAGE_SIZE |
		 MLX5_MKEY_MASK_START_ADDR;

	return cpu_to_be64(result);
}
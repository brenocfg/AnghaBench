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
typedef  scalar_t__ u32 ;
struct sdma_script_start_addrs {int dummy; } ;
struct sdma_engine {int script_number; scalar_t__ script_addrs; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V1 ; 

__attribute__((used)) static void sdma_add_scripts(struct sdma_engine *sdma,
		const struct sdma_script_start_addrs *addr)
{
	s32 *addr_arr = (u32 *)addr;
	s32 *saddr_arr = (u32 *)sdma->script_addrs;
	int i;

	/* use the default firmware in ROM if missing external firmware */
	if (!sdma->script_number)
		sdma->script_number = SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V1;

	for (i = 0; i < sdma->script_number; i++)
		if (addr_arr[i] > 0)
			saddr_arr[i] = addr_arr[i];
}
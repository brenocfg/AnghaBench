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

/* Variables and functions */
 scalar_t__ ZIIRAVE_FIRM_FLASH_MEMORY_END ; 
 scalar_t__ ZIIRAVE_FIRM_FLASH_MEMORY_START ; 

__attribute__((used)) static bool ziirave_firm_addr_readonly(u32 addr)
{
	return addr < ZIIRAVE_FIRM_FLASH_MEMORY_START ||
	       addr > ZIIRAVE_FIRM_FLASH_MEMORY_END;
}
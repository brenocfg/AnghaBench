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
typedef  int u16 ;

/* Variables and functions */
 int SKL_DRAM_SIZE_MASK ; 

__attribute__((used)) static int skl_get_dimm_size(u16 val)
{
	return val & SKL_DRAM_SIZE_MASK;
}
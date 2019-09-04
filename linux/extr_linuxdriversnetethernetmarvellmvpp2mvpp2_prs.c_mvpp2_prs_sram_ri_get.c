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
struct mvpp2_prs_entry {int* sram; } ;

/* Variables and functions */
 size_t MVPP2_PRS_SRAM_RI_WORD ; 

__attribute__((used)) static int mvpp2_prs_sram_ri_get(struct mvpp2_prs_entry *pe)
{
	return pe->sram[MVPP2_PRS_SRAM_RI_WORD];
}
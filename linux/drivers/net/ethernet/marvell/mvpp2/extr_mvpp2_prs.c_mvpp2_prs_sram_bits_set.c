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
typedef  int u32 ;
struct mvpp2_prs_entry {int* sram; } ;

/* Variables and functions */
 int MVPP2_BIT_IN_WORD (int) ; 
 size_t MVPP2_BIT_TO_WORD (int) ; 

__attribute__((used)) static void mvpp2_prs_sram_bits_set(struct mvpp2_prs_entry *pe, int bit_num,
				    u32 val)
{
	pe->sram[MVPP2_BIT_TO_WORD(bit_num)] |= (val << (MVPP2_BIT_IN_WORD(bit_num)));
}
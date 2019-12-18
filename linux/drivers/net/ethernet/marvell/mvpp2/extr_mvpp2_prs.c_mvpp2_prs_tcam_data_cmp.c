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
struct mvpp2_prs_entry {int* tcam; } ;

/* Variables and functions */
 size_t MVPP2_PRS_BYTE_TO_WORD (int) ; 

__attribute__((used)) static bool mvpp2_prs_tcam_data_cmp(struct mvpp2_prs_entry *pe, int offs,
				    u16 data)
{
	u16 tcam_data;

	tcam_data = pe->tcam[MVPP2_PRS_BYTE_TO_WORD(offs)] & 0xffff;
	return tcam_data == data;
}
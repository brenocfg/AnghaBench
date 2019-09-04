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
typedef  int uint ;
typedef  int loff_t ;

/* Variables and functions */
 int DOC_LAYOUT_NBPLANES ; 
 int DOC_LAYOUT_PAGES_PER_BLOCK ; 
 int DOC_LAYOUT_PAGE_OOB_SIZE ; 
 int DOC_LAYOUT_PAGE_SIZE ; 

__attribute__((used)) static void calc_block_sector(loff_t from, int *block0, int *block1, int *page,
			      int *ofs, int reliable)
{
	uint sector, pages_biblock;

	pages_biblock = DOC_LAYOUT_PAGES_PER_BLOCK * DOC_LAYOUT_NBPLANES;
	if (reliable == 1 || reliable == 2)
		pages_biblock /= 2;

	sector = from / DOC_LAYOUT_PAGE_SIZE;
	*block0 = sector / pages_biblock * DOC_LAYOUT_NBPLANES;
	*block1 = *block0 + 1;
	*page = sector % pages_biblock;
	*page /= DOC_LAYOUT_NBPLANES;
	if (reliable == 1 || reliable == 2)
		*page *= 2;
	if (sector % 2)
		*ofs = DOC_LAYOUT_PAGE_OOB_SIZE;
	else
		*ofs = 0;
}
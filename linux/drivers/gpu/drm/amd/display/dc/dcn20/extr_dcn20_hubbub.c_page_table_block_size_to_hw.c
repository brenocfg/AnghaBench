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
typedef  enum dcn_hubbub_page_table_block_size { ____Placeholder_dcn_hubbub_page_table_block_size } dcn_hubbub_page_table_block_size ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DCN_PAGE_TABLE_BLOCK_SIZE_4KB ; 
 int DCN_PAGE_TABLE_BLOCK_SIZE_64KB ; 

__attribute__((used)) static enum dcn_hubbub_page_table_block_size page_table_block_size_to_hw(unsigned int page_table_block_size)
{
	enum dcn_hubbub_page_table_block_size block_size = 0;

	switch (page_table_block_size) {
	case 4096:
		block_size = DCN_PAGE_TABLE_BLOCK_SIZE_4KB;
		break;
	case 65536:
		block_size = DCN_PAGE_TABLE_BLOCK_SIZE_64KB;
		break;
	default:
		ASSERT(false);
		block_size = page_table_block_size;
		break;
	}

	return block_size;
}
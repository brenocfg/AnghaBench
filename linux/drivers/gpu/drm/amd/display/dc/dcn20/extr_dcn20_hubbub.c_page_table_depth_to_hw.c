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
typedef  enum dcn_hubbub_page_table_depth { ____Placeholder_dcn_hubbub_page_table_depth } dcn_hubbub_page_table_depth ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DCN_PAGE_TABLE_DEPTH_1_LEVEL ; 
 int DCN_PAGE_TABLE_DEPTH_2_LEVEL ; 
 int DCN_PAGE_TABLE_DEPTH_3_LEVEL ; 
 int DCN_PAGE_TABLE_DEPTH_4_LEVEL ; 

__attribute__((used)) static enum dcn_hubbub_page_table_depth page_table_depth_to_hw(unsigned int page_table_depth)
{
	enum dcn_hubbub_page_table_depth depth = 0;

	switch (page_table_depth) {
	case 1:
		depth = DCN_PAGE_TABLE_DEPTH_1_LEVEL;
		break;
	case 2:
		depth = DCN_PAGE_TABLE_DEPTH_2_LEVEL;
		break;
	case 3:
		depth = DCN_PAGE_TABLE_DEPTH_3_LEVEL;
		break;
	case 4:
		depth = DCN_PAGE_TABLE_DEPTH_4_LEVEL;
		break;
	default:
		ASSERT(false);
		break;
	}

	return depth;
}
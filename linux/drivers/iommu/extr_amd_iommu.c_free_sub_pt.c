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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  PAGE_MODE_1_LEVEL 135 
#define  PAGE_MODE_2_LEVEL 134 
#define  PAGE_MODE_3_LEVEL 133 
#define  PAGE_MODE_4_LEVEL 132 
#define  PAGE_MODE_5_LEVEL 131 
#define  PAGE_MODE_6_LEVEL 130 
#define  PAGE_MODE_7_LEVEL 129 
#define  PAGE_MODE_NONE 128 
 struct page* free_pt_l2 (unsigned long,struct page*) ; 
 struct page* free_pt_l3 (unsigned long,struct page*) ; 
 struct page* free_pt_l4 (unsigned long,struct page*) ; 
 struct page* free_pt_l5 (unsigned long,struct page*) ; 
 struct page* free_pt_l6 (unsigned long,struct page*) ; 
 struct page* free_pt_page (unsigned long,struct page*) ; 

__attribute__((used)) static struct page *free_sub_pt(unsigned long root, int mode,
				struct page *freelist)
{
	switch (mode) {
	case PAGE_MODE_NONE:
	case PAGE_MODE_7_LEVEL:
		break;
	case PAGE_MODE_1_LEVEL:
		freelist = free_pt_page(root, freelist);
		break;
	case PAGE_MODE_2_LEVEL:
		freelist = free_pt_l2(root, freelist);
		break;
	case PAGE_MODE_3_LEVEL:
		freelist = free_pt_l3(root, freelist);
		break;
	case PAGE_MODE_4_LEVEL:
		freelist = free_pt_l4(root, freelist);
		break;
	case PAGE_MODE_5_LEVEL:
		freelist = free_pt_l5(root, freelist);
		break;
	case PAGE_MODE_6_LEVEL:
		freelist = free_pt_l6(root, freelist);
		break;
	default:
		BUG();
	}

	return freelist;
}
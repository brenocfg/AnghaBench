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
struct protection_domain {int mode; scalar_t__ pt_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  PAGE_MODE_1_LEVEL 134 
#define  PAGE_MODE_2_LEVEL 133 
#define  PAGE_MODE_3_LEVEL 132 
#define  PAGE_MODE_4_LEVEL 131 
#define  PAGE_MODE_5_LEVEL 130 
#define  PAGE_MODE_6_LEVEL 129 
#define  PAGE_MODE_NONE 128 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_pt_l2 (unsigned long) ; 
 int /*<<< orphan*/  free_pt_l3 (unsigned long) ; 
 int /*<<< orphan*/  free_pt_l4 (unsigned long) ; 
 int /*<<< orphan*/  free_pt_l5 (unsigned long) ; 
 int /*<<< orphan*/  free_pt_l6 (unsigned long) ; 

__attribute__((used)) static void free_pagetable(struct protection_domain *domain)
{
	unsigned long root = (unsigned long)domain->pt_root;

	switch (domain->mode) {
	case PAGE_MODE_NONE:
		break;
	case PAGE_MODE_1_LEVEL:
		free_page(root);
		break;
	case PAGE_MODE_2_LEVEL:
		free_pt_l2(root);
		break;
	case PAGE_MODE_3_LEVEL:
		free_pt_l3(root);
		break;
	case PAGE_MODE_4_LEVEL:
		free_pt_l4(root);
		break;
	case PAGE_MODE_5_LEVEL:
		free_pt_l5(root);
		break;
	case PAGE_MODE_6_LEVEL:
		free_pt_l6(root);
		break;
	default:
		BUG();
	}
}
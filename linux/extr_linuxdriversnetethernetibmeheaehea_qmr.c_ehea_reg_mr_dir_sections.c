#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ehea_mr {int dummy; } ;
struct ehea_adapter {int dummy; } ;
struct TYPE_4__ {TYPE_1__** top; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dir; } ;

/* Variables and functions */
 int EHEA_MAP_ENTRIES ; 
 scalar_t__ H_PAGE_REGISTERED ; 
 scalar_t__ H_SUCCESS ; 
 TYPE_2__* ehea_bmap ; 
 scalar_t__ ehea_reg_mr_sections (int,int,scalar_t__*,struct ehea_adapter*,struct ehea_mr*) ; 

__attribute__((used)) static u64 ehea_reg_mr_dir_sections(int top, u64 *pt,
				    struct ehea_adapter *adapter,
				    struct ehea_mr *mr)
{
	u64 hret = H_SUCCESS;
	int dir;

	for (dir = 0; dir < EHEA_MAP_ENTRIES; dir++) {
		if (!ehea_bmap->top[top]->dir[dir])
			continue;

		hret = ehea_reg_mr_sections(top, dir, pt, adapter, mr);
		if ((hret != H_SUCCESS) && (hret != H_PAGE_REGISTERED))
			return hret;
	}
	return hret;
}
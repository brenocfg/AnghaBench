#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ehea_mr {int dummy; } ;
struct ehea_adapter {int dummy; } ;
struct TYPE_6__ {TYPE_2__** top; } ;
struct TYPE_5__ {TYPE_1__** dir; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ent; } ;

/* Variables and functions */
 int EHEA_MAP_ENTRIES ; 
 scalar_t__ H_PAGE_REGISTERED ; 
 scalar_t__ H_SUCCESS ; 
 TYPE_3__* ehea_bmap ; 
 scalar_t__ ehea_reg_mr_section (int,int,int,scalar_t__*,struct ehea_adapter*,struct ehea_mr*) ; 

__attribute__((used)) static u64 ehea_reg_mr_sections(int top, int dir, u64 *pt,
				struct ehea_adapter *adapter,
				struct ehea_mr *mr)
{
	u64 hret = H_SUCCESS;
	int idx;

	for (idx = 0; idx < EHEA_MAP_ENTRIES; idx++) {
		if (!ehea_bmap->top[top]->dir[dir]->ent[idx])
			continue;

		hret = ehea_reg_mr_section(top, dir, idx, pt, adapter, mr);
		if ((hret != H_SUCCESS) && (hret != H_PAGE_REGISTERED))
			return hret;
	}
	return hret;
}
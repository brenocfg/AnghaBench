#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pvr2_ctrl {TYPE_4__* info; } ;
struct TYPE_6__ {int min_value; int max_value; } ;
struct TYPE_5__ {int count; } ;
struct TYPE_7__ {TYPE_2__ type_int; TYPE_1__ type_enum; } ;
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  (* get_max_value ) (struct pvr2_ctrl*,int*) ;TYPE_3__ def; int /*<<< orphan*/  (* get_min_value ) (struct pvr2_ctrl*,int*) ;int /*<<< orphan*/  (* check_value ) (struct pvr2_ctrl*,int) ;} ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ pvr2_ctl_enum ; 
 int /*<<< orphan*/  stub1 (struct pvr2_ctrl*,int) ; 
 int /*<<< orphan*/  stub2 (struct pvr2_ctrl*,int*) ; 
 int /*<<< orphan*/  stub3 (struct pvr2_ctrl*,int*) ; 

__attribute__((used)) static int pvr2_ctrl_range_check(struct pvr2_ctrl *cptr,int val)
{
	if (cptr->info->check_value) {
		if (!cptr->info->check_value(cptr,val)) return -ERANGE;
	} else if (cptr->info->type == pvr2_ctl_enum) {
		if (val < 0) return -ERANGE;
		if (val >= cptr->info->def.type_enum.count) return -ERANGE;
	} else {
		int lim;
		lim = cptr->info->def.type_int.min_value;
		if (cptr->info->get_min_value) {
			cptr->info->get_min_value(cptr,&lim);
		}
		if (val < lim) return -ERANGE;
		lim = cptr->info->def.type_int.max_value;
		if (cptr->info->get_max_value) {
			cptr->info->get_max_value(cptr,&lim);
		}
		if (val > lim) return -ERANGE;
	}
	return 0;
}
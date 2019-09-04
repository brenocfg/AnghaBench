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
typedef  int mm_segment_t ;
struct TYPE_6__ {int /*<<< orphan*/  kernel_asce; int /*<<< orphan*/  user_asce; } ;
struct TYPE_4__ {int mm_segment; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIF_ASCE_PRIMARY ; 
 int /*<<< orphan*/  CIF_ASCE_SECONDARY ; 
 TYPE_3__ S390_lowcore ; 
 int USER_DS ; 
 int USER_DS_SACF ; 
 int /*<<< orphan*/  __ctl_load (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clear_cpu_flag (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  set_cpu_flag (int /*<<< orphan*/ ) ; 

void set_fs(mm_segment_t fs)
{
	current->thread.mm_segment = fs;
	if (fs == USER_DS) {
		__ctl_load(S390_lowcore.user_asce, 1, 1);
		clear_cpu_flag(CIF_ASCE_PRIMARY);
	} else {
		__ctl_load(S390_lowcore.kernel_asce, 1, 1);
		set_cpu_flag(CIF_ASCE_PRIMARY);
	}
	if (fs & 1) {
		if (fs == USER_DS_SACF)
			__ctl_load(S390_lowcore.user_asce, 7, 7);
		else
			__ctl_load(S390_lowcore.kernel_asce, 7, 7);
		set_cpu_flag(CIF_ASCE_SECONDARY);
	}
}
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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {scalar_t__ q; } ;
struct TYPE_6__ {TYPE_1__ reg; int /*<<< orphan*/  msr_no; } ;
struct saved_msr {int valid; TYPE_2__ info; } ;
struct TYPE_7__ {int num; struct saved_msr* array; } ;
struct TYPE_8__ {TYPE_3__ saved_msrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct saved_msr* kmalloc_array (int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_4__ saved_context ; 

__attribute__((used)) static int msr_init_context(const u32 *msr_id, const int total_num)
{
	int i = 0;
	struct saved_msr *msr_array;

	if (saved_context.saved_msrs.array || saved_context.saved_msrs.num > 0) {
		pr_err("x86/pm: MSR quirk already applied, please check your DMI match table.\n");
		return -EINVAL;
	}

	msr_array = kmalloc_array(total_num, sizeof(struct saved_msr), GFP_KERNEL);
	if (!msr_array) {
		pr_err("x86/pm: Can not allocate memory to save/restore MSRs during suspend.\n");
		return -ENOMEM;
	}

	for (i = 0; i < total_num; i++) {
		msr_array[i].info.msr_no	= msr_id[i];
		msr_array[i].valid		= false;
		msr_array[i].info.reg.q		= 0;
	}
	saved_context.saved_msrs.num	= total_num;
	saved_context.saved_msrs.array	= msr_array;

	return 0;
}
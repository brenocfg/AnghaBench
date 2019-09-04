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
struct TYPE_5__ {int /*<<< orphan*/  q; } ;
struct TYPE_6__ {TYPE_2__ reg; int /*<<< orphan*/  msr_no; } ;
struct saved_msr {int valid; TYPE_3__ info; } ;
struct TYPE_4__ {int num; struct saved_msr* array; } ;
struct saved_context {TYPE_1__ saved_msrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdmsrl_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msr_save_context(struct saved_context *ctxt)
{
	struct saved_msr *msr = ctxt->saved_msrs.array;
	struct saved_msr *end = msr + ctxt->saved_msrs.num;

	while (msr < end) {
		msr->valid = !rdmsrl_safe(msr->info.msr_no, &msr->info.reg.q);
		msr++;
	}
}
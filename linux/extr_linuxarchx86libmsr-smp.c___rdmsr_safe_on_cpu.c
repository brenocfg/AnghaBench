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
struct TYPE_3__ {int /*<<< orphan*/  h; int /*<<< orphan*/  l; } ;
struct TYPE_4__ {TYPE_1__ reg; int /*<<< orphan*/  msr_no; int /*<<< orphan*/  err; } ;
struct msr_info_completion {int /*<<< orphan*/  done; TYPE_2__ msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdmsr_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rdmsr_safe_on_cpu(void *info)
{
	struct msr_info_completion *rv = info;

	rv->msr.err = rdmsr_safe(rv->msr.msr_no, &rv->msr.reg.l, &rv->msr.reg.h);
	complete(&rv->done);
}
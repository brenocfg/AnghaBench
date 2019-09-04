#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) () ;} ;

/* Variables and functions */
 TYPE_1__* kgd2kfd ; 
 int /*<<< orphan*/  kgd2kfd_init ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  symbol_put (int /*<<< orphan*/ ) ; 

void amdgpu_amdkfd_fini(void)
{
	if (kgd2kfd) {
		kgd2kfd->exit();
		symbol_put(kgd2kfd_init);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {int parity_check; } ;
typedef  TYPE_2__ FAS216_Info ;

/* Variables and functions */

__attribute__((used)) static int parity_test(FAS216_Info *info, int target)
{
#if 0
	if (target == 3) {
		info->device[target].parity_check = 0;
		return 1;
	}
#endif
	return info->device[target].parity_check;
}
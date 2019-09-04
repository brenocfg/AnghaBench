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
struct TYPE_2__ {scalar_t__ CurrentBus; scalar_t__ CurrentTargetID; } ;
typedef  TYPE_1__ FCDevicePage0_t ;

/* Variables and functions */

__attribute__((used)) static int
mptfc_FcDevPage0_cmp_func(const void *a, const void *b)
{
	FCDevicePage0_t **aa = (FCDevicePage0_t **)a;
	FCDevicePage0_t **bb = (FCDevicePage0_t **)b;

	if ((*aa)->CurrentBus == (*bb)->CurrentBus) {
		if ((*aa)->CurrentTargetID == (*bb)->CurrentTargetID)
			return 0;
		if ((*aa)->CurrentTargetID < (*bb)->CurrentTargetID)
			return -1;
		return 1;
	}
	if ((*aa)->CurrentBus < (*bb)->CurrentBus)
		return -1;
	return 1;
}
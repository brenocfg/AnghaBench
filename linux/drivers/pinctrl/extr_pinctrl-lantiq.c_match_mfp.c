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
struct ltq_pinmux_info {int num_mfp; TYPE_1__* mfp; } ;
struct TYPE_2__ {int pin; } ;

/* Variables and functions */

__attribute__((used)) static int match_mfp(const struct ltq_pinmux_info *info, int pin)
{
	int i;
	for (i = 0; i < info->num_mfp; i++) {
		if (info->mfp[i].pin == pin)
			return i;
	}
	return -1;
}
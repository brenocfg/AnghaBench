#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ s16 ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static int var_inter(const s16 *old, const s16 *new)
{
	int32_t ret = 0;
	int i;

	for (i = 0; i < 8 * 8; i++, old++, new++)
		ret += (*old - *new) < 0 ? -(*old - *new) : (*old - *new);
	return ret;
}
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
typedef  scalar_t__ u32 ;

/* Variables and functions */

__attribute__((used)) static int uvcg_config_compare_u32(const void *l, const void *r)
{
	u32 li = *(const u32 *)l;
	u32 ri = *(const u32 *)r;

	return li < ri ? -1 : li == ri ? 0 : 1;
}
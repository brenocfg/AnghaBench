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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int convert_burst(u32 maxburst)
{
	if (maxburst > 8)
		return -EINVAL;

	/* 1 -> 0, 4 -> 1, 8 -> 2 */
	return (maxburst >> 2);
}
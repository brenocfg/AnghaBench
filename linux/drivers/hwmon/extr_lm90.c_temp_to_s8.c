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
typedef  int s8 ;

/* Variables and functions */

__attribute__((used)) static s8 temp_to_s8(long val)
{
	if (val <= -128000)
		return -128;
	if (val >= 127000)
		return 127;
	if (val < 0)
		return (val - 500) / 1000;
	return (val + 500) / 1000;
}
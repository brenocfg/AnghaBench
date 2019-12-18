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

/* Variables and functions */
 int clamp_val (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int FAN_TO_REG(long val, int tpc)
{
	if (tpc) {
		return clamp_val(val / tpc, 0, 0xffff);
	} else {
		return (val <= 0) ? 0xffff :
			clamp_val(90000 * 60 / val, 0, 0xfffe);
	}
}
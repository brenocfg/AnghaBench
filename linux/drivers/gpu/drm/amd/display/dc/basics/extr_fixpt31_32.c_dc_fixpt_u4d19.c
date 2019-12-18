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
struct fixed31_32 {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 unsigned int ux_dy (int /*<<< orphan*/ ,int,int) ; 

unsigned int dc_fixpt_u4d19(struct fixed31_32 arg)
{
	return ux_dy(arg.value, 4, 19);
}
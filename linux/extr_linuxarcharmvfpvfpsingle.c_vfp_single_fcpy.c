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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  vfp_put_float (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 vfp_single_fcpy(int sd, int unused, s32 m, u32 fpscr)
{
	vfp_put_float(m, sd);
	return 0;
}
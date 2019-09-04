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
struct vfp_single {int exponent; scalar_t__ significand; scalar_t__ sign; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ vfp_single_normaliseround (int,struct vfp_single*,scalar_t__,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u32 vfp_single_fuito(int sd, int unused, s32 m, u32 fpscr)
{
	struct vfp_single vs;

	vs.sign = 0;
	vs.exponent = 127 + 31 - 1;
	vs.significand = (u32)m;

	return vfp_single_normaliseround(sd, &vs, fpscr, 0, "fuito");
}
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
 int /*<<< orphan*/  vfp_single_fadd (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_single_packed_negate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 vfp_single_fsub(int sd, int sn, s32 m, u32 fpscr)
{
	/*
	 * Subtraction is addition with one sign inverted.
	 */
	return vfp_single_fadd(sd, sn, vfp_single_packed_negate(m), fpscr);
}
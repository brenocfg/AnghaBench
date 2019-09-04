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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  atom_exec_context ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_SRC_BYTE0 ; 
 int /*<<< orphan*/  SDEBUG (char*,...) ; 
 int U8 (int /*<<< orphan*/ ) ; 
 int* atom_def_dst ; 
 int atom_get_dst (int /*<<< orphan*/ *,int,int,int*,int*,int) ; 
 int atom_get_src_direct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  atom_put_dst (int /*<<< orphan*/ *,int,int,int*,int,int) ; 

__attribute__((used)) static void atom_op_shift_left(atom_exec_context *ctx, int *ptr, int arg)
{
	uint8_t attr = U8((*ptr)++), shift;
	uint32_t saved, dst;
	int dptr = *ptr;
	attr &= 0x38;
	attr |= atom_def_dst[attr >> 3] << 6;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	shift = atom_get_src_direct(ctx, ATOM_SRC_BYTE0, ptr);
	SDEBUG("   shift: %d\n", shift);
	dst <<= shift;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
}
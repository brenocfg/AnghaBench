#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {TYPE_1__* ctx; } ;
typedef  TYPE_2__ atom_exec_context ;
struct TYPE_6__ {int /*<<< orphan*/ * divmul; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEBUG (char*) ; 
 int /*<<< orphan*/  U8 (int /*<<< orphan*/ ) ; 
 scalar_t__ atom_get_dst (TYPE_2__*,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ atom_get_src (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static void atom_op_mul32(atom_exec_context *ctx, int *ptr, int arg)
{
	uint64_t val64;
	uint8_t attr = U8((*ptr)++);
	uint32_t dst, src;
	SDEBUG("   src1: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, NULL, 1);
	SDEBUG("   src2: ");
	src = atom_get_src(ctx, attr, ptr);
	val64 = (uint64_t)dst * (uint64_t)src;
	ctx->ctx->divmul[0] = lower_32_bits(val64);
	ctx->ctx->divmul[1] = upper_32_bits(val64);
}
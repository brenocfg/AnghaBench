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
typedef  int uint32_t ;
struct TYPE_7__ {TYPE_1__* ctx; } ;
typedef  TYPE_2__ atom_exec_context ;
struct TYPE_6__ {int* divmul; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEBUG (char*) ; 
 int /*<<< orphan*/  U8 (int /*<<< orphan*/ ) ; 
 int atom_get_dst (TYPE_2__*,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int) ; 
 int atom_get_src (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void atom_op_mul(atom_exec_context *ctx, int *ptr, int arg)
{
	uint8_t attr = U8((*ptr)++);
	uint32_t dst, src;
	SDEBUG("   src1: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, NULL, 1);
	SDEBUG("   src2: ");
	src = atom_get_src(ctx, attr, ptr);
	ctx->ctx->divmul[0] = dst * src;
}
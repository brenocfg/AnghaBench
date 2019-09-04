#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ctx; } ;
typedef  TYPE_2__ atom_exec_context ;
struct TYPE_4__ {int /*<<< orphan*/  reg_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U16 (int) ; 

__attribute__((used)) static void atom_op_setregblock(atom_exec_context *ctx, int *ptr, int arg)
{
	ctx->ctx->reg_block = U16(*ptr);
	(*ptr) += 2;
	SDEBUG("   base: 0x%04X\n", ctx->ctx->reg_block);
}
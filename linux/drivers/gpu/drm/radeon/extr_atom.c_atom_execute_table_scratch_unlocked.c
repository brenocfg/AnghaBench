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
typedef  int /*<<< orphan*/  uint32_t ;
struct atom_context {int /*<<< orphan*/  mutex; scalar_t__* divmul; int /*<<< orphan*/  io_mode; scalar_t__ fb_base; scalar_t__ reg_block; scalar_t__ data_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_IO_MM ; 
 int atom_execute_table_locked (struct atom_context*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int atom_execute_table_scratch_unlocked(struct atom_context *ctx, int index, uint32_t * params)
{
	int r;

	mutex_lock(&ctx->mutex);
	/* reset data block */
	ctx->data_block = 0;
	/* reset reg block */
	ctx->reg_block = 0;
	/* reset fb window */
	ctx->fb_base = 0;
	/* reset io mode */
	ctx->io_mode = ATOM_IO_MM;
	/* reset divmul */
	ctx->divmul[0] = 0;
	ctx->divmul[1] = 0;
	r = atom_execute_table_locked(ctx, index, params);
	mutex_unlock(&ctx->mutex);
	return r;
}
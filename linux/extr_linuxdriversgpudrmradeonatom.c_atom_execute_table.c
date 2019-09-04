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
struct atom_context {int /*<<< orphan*/  scratch_mutex; } ;

/* Variables and functions */
 int atom_execute_table_scratch_unlocked (struct atom_context*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int atom_execute_table(struct atom_context *ctx, int index, uint32_t * params)
{
	int r;
	mutex_lock(&ctx->scratch_mutex);
	r = atom_execute_table_scratch_unlocked(ctx, index, params);
	mutex_unlock(&ctx->scratch_mutex);
	return r;
}
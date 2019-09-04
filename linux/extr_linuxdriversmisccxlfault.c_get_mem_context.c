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
struct mm_struct {int /*<<< orphan*/  mm_users; } ;
struct cxl_context {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mm_struct *get_mem_context(struct cxl_context *ctx)
{
	if (ctx->mm == NULL)
		return NULL;

	if (!atomic_inc_not_zero(&ctx->mm->mm_users))
		return NULL;

	return ctx->mm;
}
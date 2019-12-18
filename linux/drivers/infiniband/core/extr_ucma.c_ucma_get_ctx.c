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
struct ucma_file {int dummy; } ;
struct ucma_context {int /*<<< orphan*/  ref; scalar_t__ closing; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct ucma_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct ucma_context*) ; 
 struct ucma_context* _ucma_find_context (int,struct ucma_file*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctx_table ; 
 int /*<<< orphan*/  xa_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ucma_context *ucma_get_ctx(struct ucma_file *file, int id)
{
	struct ucma_context *ctx;

	xa_lock(&ctx_table);
	ctx = _ucma_find_context(id, file);
	if (!IS_ERR(ctx)) {
		if (ctx->closing)
			ctx = ERR_PTR(-EIO);
		else
			atomic_inc(&ctx->ref);
	}
	xa_unlock(&ctx_table);
	return ctx;
}
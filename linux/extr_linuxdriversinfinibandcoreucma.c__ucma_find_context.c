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
struct ucma_context {int /*<<< orphan*/  cm_id; struct ucma_file* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct ucma_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx_idr ; 
 struct ucma_context* idr_find (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline struct ucma_context *_ucma_find_context(int id,
						      struct ucma_file *file)
{
	struct ucma_context *ctx;

	ctx = idr_find(&ctx_idr, id);
	if (!ctx)
		ctx = ERR_PTR(-ENOENT);
	else if (ctx->file != file || !ctx->cm_id)
		ctx = ERR_PTR(-EINVAL);
	return ctx;
}
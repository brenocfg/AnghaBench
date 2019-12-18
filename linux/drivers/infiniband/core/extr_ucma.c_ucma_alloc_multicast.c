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
struct ucma_multicast {int /*<<< orphan*/  list; int /*<<< orphan*/  id; struct ucma_context* ctx; } ;
struct ucma_context {int /*<<< orphan*/  mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ucma_multicast*) ; 
 struct ucma_multicast* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multicast_table ; 
 scalar_t__ xa_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_limit_32b ; 

__attribute__((used)) static struct ucma_multicast* ucma_alloc_multicast(struct ucma_context *ctx)
{
	struct ucma_multicast *mc;

	mc = kzalloc(sizeof(*mc), GFP_KERNEL);
	if (!mc)
		return NULL;

	mc->ctx = ctx;
	if (xa_alloc(&multicast_table, &mc->id, NULL, xa_limit_32b, GFP_KERNEL))
		goto error;

	list_add_tail(&mc->list, &ctx->mc_list);
	return mc;

error:
	kfree(mc);
	return NULL;
}
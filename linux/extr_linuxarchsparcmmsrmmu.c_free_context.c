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
struct ctx_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_free_ctxlist (struct ctx_list*) ; 
 struct ctx_list* ctx_list_pool ; 
 int /*<<< orphan*/  remove_from_ctx_list (struct ctx_list*) ; 

__attribute__((used)) static inline void free_context(int context)
{
	struct ctx_list *ctx_old;

	ctx_old = ctx_list_pool + context;
	remove_from_ctx_list(ctx_old);
	add_to_free_ctxlist(ctx_old);
}
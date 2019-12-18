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
struct kmem_cache {int dummy; } ;
struct ab_task {int /*<<< orphan*/  done; scalar_t__ result; int /*<<< orphan*/ * done_fn; int /*<<< orphan*/  task_fn; int /*<<< orphan*/  refcount; struct kmem_cache* cache; } ;
typedef  int /*<<< orphan*/  ab_task_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct ab_task* kmem_cache_alloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ab_task *ab_task_create_get(struct kmem_cache *cache,
					  ab_task_fn_t task_fn)
{
	struct ab_task *t;

	t = kmem_cache_alloc(cache, GFP_KERNEL);
	if (!t)
		return NULL;
	t->cache = cache;
	kref_init(&t->refcount);
	t->task_fn = task_fn;
	t->done_fn = NULL;
	t->result = 0;
	init_completion(&t->done);
	return t;
}
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
struct request_queue {int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 void* kmem_cache_alloc_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_cachep ; 

__attribute__((used)) static void *alloc_request_simple(gfp_t gfp_mask, void *data)
{
	struct request_queue *q = data;

	return kmem_cache_alloc_node(request_cachep, gfp_mask, q->node);
}
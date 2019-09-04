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

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * queue_cache ; 

__attribute__((used)) static void free_queue(void *p, unsigned long q_type)
{
	kmem_cache_free(queue_cache[q_type - 1], p);
}
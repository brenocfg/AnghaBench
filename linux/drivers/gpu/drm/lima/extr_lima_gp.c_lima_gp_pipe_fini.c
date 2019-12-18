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
struct lima_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lima_gp_task_slab ; 
 int /*<<< orphan*/  lima_gp_task_slab_refcnt ; 

void lima_gp_pipe_fini(struct lima_device *dev)
{
	if (!--lima_gp_task_slab_refcnt) {
		kmem_cache_destroy(lima_gp_task_slab);
		lima_gp_task_slab = NULL;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pmcraid_instance {int /*<<< orphan*/ * cmd_list; int /*<<< orphan*/  cmd_cachep; int /*<<< orphan*/  cmd_pool_name; TYPE_1__* host; } ;
struct pmcraid_cmd {int dummy; } ;
struct TYPE_2__ {int unique_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PMCRAID_MAX_CMD ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcraid_release_cmd_blocks (struct pmcraid_instance*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int pmcraid_allocate_cmd_blocks(struct pmcraid_instance *pinstance)
{
	int i;

	sprintf(pinstance->cmd_pool_name, "pmcraid_cmd_pool_%d",
		pinstance->host->unique_id);


	pinstance->cmd_cachep = kmem_cache_create(
					pinstance->cmd_pool_name,
					sizeof(struct pmcraid_cmd), 0,
					SLAB_HWCACHE_ALIGN, NULL);
	if (!pinstance->cmd_cachep)
		return -ENOMEM;

	for (i = 0; i < PMCRAID_MAX_CMD; i++) {
		pinstance->cmd_list[i] =
			kmem_cache_alloc(pinstance->cmd_cachep, GFP_KERNEL);
		if (!pinstance->cmd_list[i]) {
			pmcraid_release_cmd_blocks(pinstance, i);
			return -ENOMEM;
		}
	}
	return 0;
}
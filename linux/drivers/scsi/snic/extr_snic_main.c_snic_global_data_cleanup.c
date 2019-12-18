#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * req_cache; int /*<<< orphan*/  event_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_BUG_ON (int /*<<< orphan*/ ) ; 
 size_t SNIC_REQ_CACHE_DFLT_SGL ; 
 size_t SNIC_REQ_CACHE_MAX_SGL ; 
 size_t SNIC_REQ_TM_CACHE ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snic_debugfs_term () ; 
 TYPE_1__* snic_glob ; 
 int /*<<< orphan*/  snic_trc_free () ; 

__attribute__((used)) static void
snic_global_data_cleanup(void)
{
	SNIC_BUG_ON(snic_glob == NULL);

	destroy_workqueue(snic_glob->event_q);
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_TM_CACHE]);
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_CACHE_MAX_SGL]);
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_CACHE_DFLT_SGL]);

#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
	/* Freeing Trace Resources */
	snic_trc_free();

	/* Freeing Debugfs Resources */
	snic_debugfs_term();
#endif
	kfree(snic_glob);
	snic_glob = NULL;
}
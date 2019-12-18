#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snic_req_info {int dummy; } ;
struct snic_max_sgl {int dummy; } ;
struct snic_host_req {int dummy; } ;
struct snic_dflt_sgl {int dummy; } ;
struct kmem_cache {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {struct kmem_cache** req_cache; int /*<<< orphan*/  event_q; int /*<<< orphan*/  snic_list_lock; int /*<<< orphan*/  snic_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  SNIC_ERR (char*) ; 
 size_t SNIC_REQ_CACHE_DFLT_SGL ; 
 size_t SNIC_REQ_CACHE_MAX_SGL ; 
 size_t SNIC_REQ_TM_CACHE ; 
 int /*<<< orphan*/  SNIC_SG_DESC_ALIGN ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 struct kmem_cache* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (struct kmem_cache*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snic_debugfs_init () ; 
 int /*<<< orphan*/  snic_debugfs_term () ; 
 TYPE_1__* snic_glob ; 
 int /*<<< orphan*/  snic_trc_free () ; 
 int snic_trc_init () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snic_global_data_init(void)
{
	int ret = 0;
	struct kmem_cache *cachep;
	ssize_t len = 0;

	snic_glob = kzalloc(sizeof(*snic_glob), GFP_KERNEL);

	if (!snic_glob) {
		SNIC_ERR("Failed to allocate Global Context.\n");

		ret = -ENOMEM;
		goto gdi_end;
	}

#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
	/* Debugfs related Initialization */
	/* Create debugfs entries for snic */
	snic_debugfs_init();

	/* Trace related Initialization */
	/* Allocate memory for trace buffer */
	ret = snic_trc_init();
	if (ret < 0) {
		SNIC_ERR("Trace buffer init failed, SNIC tracing disabled\n");
		snic_trc_free();
		/* continue even if it fails */
	}

#endif
	INIT_LIST_HEAD(&snic_glob->snic_list);
	spin_lock_init(&snic_glob->snic_list_lock);

	/* Create a cache for allocation of snic_host_req+default size ESGLs */
	len = sizeof(struct snic_req_info);
	len += sizeof(struct snic_host_req) + sizeof(struct snic_dflt_sgl);
	cachep = kmem_cache_create("snic_req_dfltsgl", len, SNIC_SG_DESC_ALIGN,
				   SLAB_HWCACHE_ALIGN, NULL);
	if (!cachep) {
		SNIC_ERR("Failed to create snic default sgl slab\n");
		ret = -ENOMEM;

		goto err_dflt_req_slab;
	}
	snic_glob->req_cache[SNIC_REQ_CACHE_DFLT_SGL] = cachep;

	/* Create a cache for allocation of max size Extended SGLs */
	len = sizeof(struct snic_req_info);
	len += sizeof(struct snic_host_req) + sizeof(struct snic_max_sgl);
	cachep = kmem_cache_create("snic_req_maxsgl", len, SNIC_SG_DESC_ALIGN,
				   SLAB_HWCACHE_ALIGN, NULL);
	if (!cachep) {
		SNIC_ERR("Failed to create snic max sgl slab\n");
		ret = -ENOMEM;

		goto err_max_req_slab;
	}
	snic_glob->req_cache[SNIC_REQ_CACHE_MAX_SGL] = cachep;

	len = sizeof(struct snic_host_req);
	cachep = kmem_cache_create("snic_req_maxsgl", len, SNIC_SG_DESC_ALIGN,
				   SLAB_HWCACHE_ALIGN, NULL);
	if (!cachep) {
		SNIC_ERR("Failed to create snic tm req slab\n");
		ret = -ENOMEM;

		goto err_tmreq_slab;
	}
	snic_glob->req_cache[SNIC_REQ_TM_CACHE] = cachep;

	/* snic_event queue */
	snic_glob->event_q = create_singlethread_workqueue("snic_event_wq");
	if (!snic_glob->event_q) {
		SNIC_ERR("snic event queue create failed\n");
		ret = -ENOMEM;

		goto err_eventq;
	}

	return ret;

err_eventq:
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_TM_CACHE]);

err_tmreq_slab:
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_CACHE_MAX_SGL]);

err_max_req_slab:
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_CACHE_DFLT_SGL]);

err_dflt_req_slab:
#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
	snic_trc_free();
	snic_debugfs_term();
#endif
	kfree(snic_glob);
	snic_glob = NULL;

gdi_end:
	return ret;
}
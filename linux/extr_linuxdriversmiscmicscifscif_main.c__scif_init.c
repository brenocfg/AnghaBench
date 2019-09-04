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
struct TYPE_2__ {int p2p_enable; int /*<<< orphan*/  conn_work; int /*<<< orphan*/  mmu_notif_work; int /*<<< orphan*/  misc_work; scalar_t__ en_msg_log; int /*<<< orphan*/  rma_tc_limit; int /*<<< orphan*/  exitwq; int /*<<< orphan*/  nb_connect_list; int /*<<< orphan*/  fence; int /*<<< orphan*/  mmu_notif_cleanup; int /*<<< orphan*/  rma_tc; int /*<<< orphan*/  rma; int /*<<< orphan*/  disconnected; int /*<<< orphan*/  connected; int /*<<< orphan*/  zombie; int /*<<< orphan*/  listen; int /*<<< orphan*/  uaccept; int /*<<< orphan*/  fencelock; int /*<<< orphan*/  connlock; int /*<<< orphan*/  conflock; int /*<<< orphan*/  port_lock; int /*<<< orphan*/  nb_connect_lock; int /*<<< orphan*/  rmalock; int /*<<< orphan*/  eplock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_KMEM_UNALIGNED_BUF_SIZE ; 
 int /*<<< orphan*/  SCIF_RMA_TEMP_CACHE_LIMIT ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_conn_handler ; 
 int /*<<< orphan*/  scif_destroy_scifdev () ; 
 TYPE_1__ scif_info ; 
 int /*<<< orphan*/  scif_misc_handler ; 
 int /*<<< orphan*/  scif_mmu_notif_handler ; 
 int /*<<< orphan*/  scif_ports ; 
 int scif_setup_scifdev () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unaligned_cache ; 

__attribute__((used)) static int _scif_init(void)
{
	int rc;

	mutex_init(&scif_info.eplock);
	spin_lock_init(&scif_info.rmalock);
	spin_lock_init(&scif_info.nb_connect_lock);
	spin_lock_init(&scif_info.port_lock);
	mutex_init(&scif_info.conflock);
	mutex_init(&scif_info.connlock);
	mutex_init(&scif_info.fencelock);
	INIT_LIST_HEAD(&scif_info.uaccept);
	INIT_LIST_HEAD(&scif_info.listen);
	INIT_LIST_HEAD(&scif_info.zombie);
	INIT_LIST_HEAD(&scif_info.connected);
	INIT_LIST_HEAD(&scif_info.disconnected);
	INIT_LIST_HEAD(&scif_info.rma);
	INIT_LIST_HEAD(&scif_info.rma_tc);
	INIT_LIST_HEAD(&scif_info.mmu_notif_cleanup);
	INIT_LIST_HEAD(&scif_info.fence);
	INIT_LIST_HEAD(&scif_info.nb_connect_list);
	init_waitqueue_head(&scif_info.exitwq);
	scif_info.rma_tc_limit = SCIF_RMA_TEMP_CACHE_LIMIT;
	scif_info.en_msg_log = 0;
	scif_info.p2p_enable = 1;
	rc = scif_setup_scifdev();
	if (rc)
		goto error;
	unaligned_cache = kmem_cache_create("Unaligned_DMA",
					    SCIF_KMEM_UNALIGNED_BUF_SIZE,
					    0, SLAB_HWCACHE_ALIGN, NULL);
	if (!unaligned_cache) {
		rc = -ENOMEM;
		goto free_sdev;
	}
	INIT_WORK(&scif_info.misc_work, scif_misc_handler);
	INIT_WORK(&scif_info.mmu_notif_work, scif_mmu_notif_handler);
	INIT_WORK(&scif_info.conn_work, scif_conn_handler);
	idr_init(&scif_ports);
	return 0;
free_sdev:
	scif_destroy_scifdev();
error:
	return rc;
}
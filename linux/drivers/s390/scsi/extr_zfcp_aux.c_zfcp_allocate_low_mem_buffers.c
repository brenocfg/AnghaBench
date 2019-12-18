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
struct zfcp_fsf_req {int dummy; } ;
struct TYPE_2__ {void* gid_pn; int /*<<< orphan*/  sr_data; void* qtcb_pool; void* status_read_req; void* scsi_abort; void* scsi_req; void* gid_pn_req; void* erp_req; } ;
struct zfcp_adapter {TYPE_1__ pool; } ;
struct fsf_status_read_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int FSF_STATUS_READS_RECOM ; 
 int PAGE_SIZE ; 
 void* mempool_create_kmalloc_pool (int,int) ; 
 int /*<<< orphan*/  mempool_create_page_pool (int,int /*<<< orphan*/ ) ; 
 void* mempool_create_slab_pool (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fc_req_cache ; 
 int /*<<< orphan*/  zfcp_fsf_qtcb_cache ; 

__attribute__((used)) static int zfcp_allocate_low_mem_buffers(struct zfcp_adapter *adapter)
{
	adapter->pool.erp_req =
		mempool_create_kmalloc_pool(1, sizeof(struct zfcp_fsf_req));
	if (!adapter->pool.erp_req)
		return -ENOMEM;

	adapter->pool.gid_pn_req =
		mempool_create_kmalloc_pool(1, sizeof(struct zfcp_fsf_req));
	if (!adapter->pool.gid_pn_req)
		return -ENOMEM;

	adapter->pool.scsi_req =
		mempool_create_kmalloc_pool(1, sizeof(struct zfcp_fsf_req));
	if (!adapter->pool.scsi_req)
		return -ENOMEM;

	adapter->pool.scsi_abort =
		mempool_create_kmalloc_pool(1, sizeof(struct zfcp_fsf_req));
	if (!adapter->pool.scsi_abort)
		return -ENOMEM;

	adapter->pool.status_read_req =
		mempool_create_kmalloc_pool(FSF_STATUS_READS_RECOM,
					    sizeof(struct zfcp_fsf_req));
	if (!adapter->pool.status_read_req)
		return -ENOMEM;

	adapter->pool.qtcb_pool =
		mempool_create_slab_pool(4, zfcp_fsf_qtcb_cache);
	if (!adapter->pool.qtcb_pool)
		return -ENOMEM;

	BUILD_BUG_ON(sizeof(struct fsf_status_read_buffer) > PAGE_SIZE);
	adapter->pool.sr_data =
		mempool_create_page_pool(FSF_STATUS_READS_RECOM, 0);
	if (!adapter->pool.sr_data)
		return -ENOMEM;

	adapter->pool.gid_pn =
		mempool_create_slab_pool(1, zfcp_fc_req_cache);
	if (!adapter->pool.gid_pn)
		return -ENOMEM;

	return 0;
}
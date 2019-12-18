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
struct TYPE_2__ {int /*<<< orphan*/  gid_pn; int /*<<< orphan*/  sr_data; int /*<<< orphan*/  status_read_req; int /*<<< orphan*/  qtcb_pool; int /*<<< orphan*/  scsi_abort; int /*<<< orphan*/  scsi_req; int /*<<< orphan*/  erp_req; } ;
struct zfcp_adapter {TYPE_1__ pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_free_low_mem_buffers(struct zfcp_adapter *adapter)
{
	mempool_destroy(adapter->pool.erp_req);
	mempool_destroy(adapter->pool.scsi_req);
	mempool_destroy(adapter->pool.scsi_abort);
	mempool_destroy(adapter->pool.qtcb_pool);
	mempool_destroy(adapter->pool.status_read_req);
	mempool_destroy(adapter->pool.sr_data);
	mempool_destroy(adapter->pool.gid_pn);
}
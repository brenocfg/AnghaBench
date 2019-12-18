#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zfcp_fsf_req {int pool; struct zfcp_fsf_req* qtcb; TYPE_2__* adapter; } ;
struct TYPE_3__ {int qtcb_pool; } ;
struct TYPE_4__ {TYPE_1__ pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct zfcp_fsf_req*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mempool_free (struct zfcp_fsf_req*,int) ; 
 int /*<<< orphan*/  zfcp_fsf_qtcb_cache ; 
 int /*<<< orphan*/  zfcp_fsf_req_is_status_read_buffer (struct zfcp_fsf_req*) ; 

void zfcp_fsf_req_free(struct zfcp_fsf_req *req)
{
	if (likely(req->pool)) {
		if (likely(!zfcp_fsf_req_is_status_read_buffer(req)))
			mempool_free(req->qtcb, req->adapter->pool.qtcb_pool);
		mempool_free(req, req->pool);
		return;
	}

	if (likely(!zfcp_fsf_req_is_status_read_buffer(req)))
		kmem_cache_free(zfcp_fsf_qtcb_cache, req->qtcb);
	kfree(req);
}
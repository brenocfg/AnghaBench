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
struct sockaddr_storage {int dummy; } ;
typedef  struct sockaddr_storage sockaddr ;
struct TYPE_3__ {scalar_t__ (* event_handler ) (TYPE_1__*,struct rdma_cm_event*) ;} ;
struct rdma_id_private {int /*<<< orphan*/  handler_mutex; TYPE_1__ id; int /*<<< orphan*/  cma_dev; } ;
struct rdma_dev_addr {int dummy; } ;
struct rdma_cm_event {int status; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_CM_ADDR_BOUND ; 
 int /*<<< orphan*/  RDMA_CM_ADDR_QUERY ; 
 int /*<<< orphan*/  RDMA_CM_ADDR_RESOLVED ; 
 int /*<<< orphan*/  RDMA_CM_DESTROYING ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_ADDR_ERROR ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_ADDR_RESOLVED ; 
 int cma_acquire_dev_by_src_ip (struct rdma_id_private*) ; 
 int /*<<< orphan*/  cma_comp_exch (struct rdma_id_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cma_exch (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 struct sockaddr_storage* cma_src_addr (struct rdma_id_private*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug_ratelimited (char*,int) ; 
 int /*<<< orphan*/  rdma_addr_size (struct sockaddr_storage*) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_1__*) ; 
 scalar_t__ stub1 (TYPE_1__*,struct rdma_cm_event*) ; 

__attribute__((used)) static void addr_handler(int status, struct sockaddr *src_addr,
			 struct rdma_dev_addr *dev_addr, void *context)
{
	struct rdma_id_private *id_priv = context;
	struct rdma_cm_event event = {};
	struct sockaddr *addr;
	struct sockaddr_storage old_addr;

	mutex_lock(&id_priv->handler_mutex);
	if (!cma_comp_exch(id_priv, RDMA_CM_ADDR_QUERY,
			   RDMA_CM_ADDR_RESOLVED))
		goto out;

	/*
	 * Store the previous src address, so that if we fail to acquire
	 * matching rdma device, old address can be restored back, which helps
	 * to cancel the cma listen operation correctly.
	 */
	addr = cma_src_addr(id_priv);
	memcpy(&old_addr, addr, rdma_addr_size(addr));
	memcpy(addr, src_addr, rdma_addr_size(src_addr));
	if (!status && !id_priv->cma_dev) {
		status = cma_acquire_dev_by_src_ip(id_priv);
		if (status)
			pr_debug_ratelimited("RDMA CM: ADDR_ERROR: failed to acquire device. status %d\n",
					     status);
	} else if (status) {
		pr_debug_ratelimited("RDMA CM: ADDR_ERROR: failed to resolve IP. status %d\n", status);
	}

	if (status) {
		memcpy(addr, &old_addr,
		       rdma_addr_size((struct sockaddr *)&old_addr));
		if (!cma_comp_exch(id_priv, RDMA_CM_ADDR_RESOLVED,
				   RDMA_CM_ADDR_BOUND))
			goto out;
		event.event = RDMA_CM_EVENT_ADDR_ERROR;
		event.status = status;
	} else
		event.event = RDMA_CM_EVENT_ADDR_RESOLVED;

	if (id_priv->id.event_handler(&id_priv->id, &event)) {
		cma_exch(id_priv, RDMA_CM_DESTROYING);
		mutex_unlock(&id_priv->handler_mutex);
		rdma_destroy_id(&id_priv->id);
		return;
	}
out:
	mutex_unlock(&id_priv->handler_mutex);
}
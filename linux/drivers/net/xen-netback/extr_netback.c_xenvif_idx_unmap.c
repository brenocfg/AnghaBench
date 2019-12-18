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
typedef  size_t u16 ;
struct xenvif_queue {TYPE_1__* vif; int /*<<< orphan*/ * mmap_pages; int /*<<< orphan*/ * grant_tx_handle; } ;
struct gnttab_unmap_grant_ref {int /*<<< orphan*/  status; int /*<<< orphan*/  handle; int /*<<< orphan*/  host_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GNTMAP_host_map ; 
 int /*<<< orphan*/  gnttab_set_unmap_op (struct gnttab_unmap_grant_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnttab_unmap_refs (struct gnttab_unmap_grant_ref*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idx_to_kaddr (struct xenvif_queue*,size_t) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenvif_grant_handle_reset (struct xenvif_queue*,size_t) ; 

void xenvif_idx_unmap(struct xenvif_queue *queue, u16 pending_idx)
{
	int ret;
	struct gnttab_unmap_grant_ref tx_unmap_op;

	gnttab_set_unmap_op(&tx_unmap_op,
			    idx_to_kaddr(queue, pending_idx),
			    GNTMAP_host_map,
			    queue->grant_tx_handle[pending_idx]);
	xenvif_grant_handle_reset(queue, pending_idx);

	ret = gnttab_unmap_refs(&tx_unmap_op, NULL,
				&queue->mmap_pages[pending_idx], 1);
	if (ret) {
		netdev_err(queue->vif->dev,
			   "Unmap fail: ret: %d pending_idx: %d host_addr: %llx handle: 0x%x status: %d\n",
			   ret,
			   pending_idx,
			   tx_unmap_op.host_addr,
			   tx_unmap_op.handle,
			   tx_unmap_op.status);
		BUG();
	}
}
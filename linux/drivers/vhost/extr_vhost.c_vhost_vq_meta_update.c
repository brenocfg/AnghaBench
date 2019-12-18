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
struct vhost_virtqueue {struct vhost_umem_node const** meta_iotlb; } ;
struct vhost_umem_node {int perm; } ;

/* Variables and functions */
 int VHOST_ACCESS_RO ; 
 int VHOST_ACCESS_WO ; 
 int VHOST_ADDR_USED ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void vhost_vq_meta_update(struct vhost_virtqueue *vq,
				 const struct vhost_umem_node *node,
				 int type)
{
	int access = (type == VHOST_ADDR_USED) ?
		     VHOST_ACCESS_WO : VHOST_ACCESS_RO;

	if (likely(node->perm & access))
		vq->meta_iotlb[type] = node;
}
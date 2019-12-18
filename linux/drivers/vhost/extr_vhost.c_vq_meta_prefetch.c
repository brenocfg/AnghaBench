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
typedef  int /*<<< orphan*/  u64 ;
struct vhost_virtqueue {unsigned int num; scalar_t__ used; scalar_t__ avail; scalar_t__ desc; int /*<<< orphan*/  iotlb; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHOST_ACCESS_RO ; 
 int /*<<< orphan*/  VHOST_ACCESS_WO ; 
 int /*<<< orphan*/  VHOST_ADDR_AVAIL ; 
 int /*<<< orphan*/  VHOST_ADDR_DESC ; 
 int /*<<< orphan*/  VHOST_ADDR_USED ; 
 scalar_t__ iotlb_access_ok (struct vhost_virtqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_get_avail_size (struct vhost_virtqueue*,unsigned int) ; 
 int /*<<< orphan*/  vhost_get_desc_size (struct vhost_virtqueue*,unsigned int) ; 
 int /*<<< orphan*/  vhost_get_used_size (struct vhost_virtqueue*,unsigned int) ; 

int vq_meta_prefetch(struct vhost_virtqueue *vq)
{
	unsigned int num = vq->num;

	if (!vq->iotlb)
		return 1;

	return iotlb_access_ok(vq, VHOST_ACCESS_RO, (u64)(uintptr_t)vq->desc,
			       vhost_get_desc_size(vq, num), VHOST_ADDR_DESC) &&
	       iotlb_access_ok(vq, VHOST_ACCESS_RO, (u64)(uintptr_t)vq->avail,
			       vhost_get_avail_size(vq, num),
			       VHOST_ADDR_AVAIL) &&
	       iotlb_access_ok(vq, VHOST_ACCESS_WO, (u64)(uintptr_t)vq->used,
			       vhost_get_used_size(vq, num), VHOST_ADDR_USED);
}
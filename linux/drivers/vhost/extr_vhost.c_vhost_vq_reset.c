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
struct vhost_virtqueue {int num; int signalled_used_valid; int log_used; unsigned long long log_addr; int /*<<< orphan*/ * iotlb; int /*<<< orphan*/ * umem; scalar_t__ busyloop_timeout; int /*<<< orphan*/ * log_ctx; int /*<<< orphan*/ * call_ctx; int /*<<< orphan*/ * kick; int /*<<< orphan*/ * error_ctx; int /*<<< orphan*/ * log_base; scalar_t__ acked_backend_features; scalar_t__ acked_features; int /*<<< orphan*/ * private_data; scalar_t__ used_flags; scalar_t__ signalled_used; scalar_t__ last_used_idx; scalar_t__ avail_idx; scalar_t__ last_avail_idx; int /*<<< orphan*/ * used; int /*<<< orphan*/ * avail; int /*<<< orphan*/ * desc; } ;
struct vhost_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vhost_vq_meta_reset (struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_disable_cross_endian (struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_reset_is_le (struct vhost_virtqueue*) ; 

__attribute__((used)) static void vhost_vq_reset(struct vhost_dev *dev,
			   struct vhost_virtqueue *vq)
{
	vq->num = 1;
	vq->desc = NULL;
	vq->avail = NULL;
	vq->used = NULL;
	vq->last_avail_idx = 0;
	vq->avail_idx = 0;
	vq->last_used_idx = 0;
	vq->signalled_used = 0;
	vq->signalled_used_valid = false;
	vq->used_flags = 0;
	vq->log_used = false;
	vq->log_addr = -1ull;
	vq->private_data = NULL;
	vq->acked_features = 0;
	vq->acked_backend_features = 0;
	vq->log_base = NULL;
	vq->error_ctx = NULL;
	vq->kick = NULL;
	vq->call_ctx = NULL;
	vq->log_ctx = NULL;
	vhost_reset_is_le(vq);
	vhost_disable_cross_endian(vq);
	vq->busyloop_timeout = 0;
	vq->umem = NULL;
	vq->iotlb = NULL;
	__vhost_vq_meta_reset(vq);
}
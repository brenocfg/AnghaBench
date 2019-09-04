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
struct virtqueue {int dummy; } ;
struct virtio_crypto_request {int /*<<< orphan*/  sgs; int /*<<< orphan*/  req_data; } ;
struct virtio_crypto {int max_data_queues; TYPE_1__* data_vq; } ;
struct TYPE_2__ {struct virtqueue* vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct virtio_crypto_request* virtqueue_detach_unused_buf (struct virtqueue*) ; 

__attribute__((used)) static void virtcrypto_free_unused_reqs(struct virtio_crypto *vcrypto)
{
	struct virtio_crypto_request *vc_req;
	int i;
	struct virtqueue *vq;

	for (i = 0; i < vcrypto->max_data_queues; i++) {
		vq = vcrypto->data_vq[i].vq;
		while ((vc_req = virtqueue_detach_unused_buf(vq)) != NULL) {
			kfree(vc_req->req_data);
			kfree(vc_req->sgs);
		}
	}
}
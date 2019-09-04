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
struct virtio_device {TYPE_1__* config; } ;
struct virtio_crypto {struct virtio_device* vdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* del_vqs ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  virtcrypto_clean_affinity (struct virtio_crypto*,int) ; 
 int /*<<< orphan*/  virtcrypto_free_queues (struct virtio_crypto*) ; 

__attribute__((used)) static void virtcrypto_del_vqs(struct virtio_crypto *vcrypto)
{
	struct virtio_device *vdev = vcrypto->vdev;

	virtcrypto_clean_affinity(vcrypto, -1);

	vdev->config->del_vqs(vdev);

	virtcrypto_free_queues(vcrypto);
}
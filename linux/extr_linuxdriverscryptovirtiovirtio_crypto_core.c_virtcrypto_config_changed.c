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
struct virtio_device {struct virtio_crypto* priv; } ;
struct virtio_crypto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtcrypto_update_status (struct virtio_crypto*) ; 

__attribute__((used)) static void virtcrypto_config_changed(struct virtio_device *vdev)
{
	struct virtio_crypto *vcrypto = vdev->priv;

	virtcrypto_update_status(vcrypto);
}
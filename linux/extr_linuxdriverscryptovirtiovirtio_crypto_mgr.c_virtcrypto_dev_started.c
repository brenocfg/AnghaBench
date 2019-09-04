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
struct virtio_crypto {int status; } ;

/* Variables and functions */
 int VIRTIO_CRYPTO_S_HW_READY ; 

int virtcrypto_dev_started(struct virtio_crypto *vcrypto_dev)
{
	return (vcrypto_dev->status & VIRTIO_CRYPTO_S_HW_READY);
}
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
struct virtio_crypto {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ virtio_crypto_algs_register (struct virtio_crypto*) ; 

int virtcrypto_dev_start(struct virtio_crypto *vcrypto)
{
	if (virtio_crypto_algs_register(vcrypto)) {
		pr_err("virtio_crypto: Failed to register crypto algs\n");
		return -EFAULT;
	}

	return 0;
}
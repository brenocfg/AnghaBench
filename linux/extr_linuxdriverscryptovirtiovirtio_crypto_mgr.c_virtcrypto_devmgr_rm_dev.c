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
struct virtio_crypto {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_devices ; 
 int /*<<< orphan*/  table_lock ; 

void virtcrypto_devmgr_rm_dev(struct virtio_crypto *vcrypto_dev)
{
	mutex_lock(&table_lock);
	list_del(&vcrypto_dev->list);
	num_devices--;
	mutex_unlock(&table_lock);
}
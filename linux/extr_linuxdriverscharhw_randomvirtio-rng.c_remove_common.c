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
struct virtrng_info {int hwrng_removed; int busy; int /*<<< orphan*/  index; int /*<<< orphan*/  hwrng; scalar_t__ hwrng_register_done; int /*<<< orphan*/  have_data; scalar_t__ data_avail; } ;
struct virtio_device {TYPE_1__* config; struct virtrng_info* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* del_vqs ) (struct virtio_device*) ;int /*<<< orphan*/  (* reset ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct virtrng_info*) ; 
 int /*<<< orphan*/  rng_index_ida ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  stub2 (struct virtio_device*) ; 

__attribute__((used)) static void remove_common(struct virtio_device *vdev)
{
	struct virtrng_info *vi = vdev->priv;

	vi->hwrng_removed = true;
	vi->data_avail = 0;
	complete(&vi->have_data);
	vdev->config->reset(vdev);
	vi->busy = false;
	if (vi->hwrng_register_done)
		hwrng_unregister(&vi->hwrng);
	vdev->config->del_vqs(vdev);
	ida_simple_remove(&rng_index_ida, vi->index);
	kfree(vi);
}
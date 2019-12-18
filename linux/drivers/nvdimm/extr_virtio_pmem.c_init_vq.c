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
struct virtio_pmem {int /*<<< orphan*/  req_list; int /*<<< orphan*/  pmem_lock; int /*<<< orphan*/  req_vq; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_find_single_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  virtio_pmem_host_ack ; 

__attribute__((used)) static int init_vq(struct virtio_pmem *vpmem)
{
	/* single vq */
	vpmem->req_vq = virtio_find_single_vq(vpmem->vdev,
					virtio_pmem_host_ack, "flush_queue");
	if (IS_ERR(vpmem->req_vq))
		return PTR_ERR(vpmem->req_vq);

	spin_lock_init(&vpmem->pmem_lock);
	INIT_LIST_HEAD(&vpmem->req_list);

	return 0;
}
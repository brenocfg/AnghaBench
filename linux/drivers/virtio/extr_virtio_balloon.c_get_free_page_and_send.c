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
struct virtqueue {int num_free; } ;
struct virtio_balloon {int /*<<< orphan*/  free_page_list_lock; int /*<<< orphan*/  num_free_page_blocks; int /*<<< orphan*/  free_page_list; struct virtqueue* free_page_vq; } ;
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_FREE_PAGE_ALLOC_FLAG ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_FREE_PAGE_ORDER ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_FREE_PAGE_SIZE ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  balloon_page_push (int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int virtqueue_add_inbuf (struct virtqueue*,struct scatterlist*,int,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ virtqueue_get_buf (struct virtqueue*,int*) ; 
 int /*<<< orphan*/  virtqueue_kick (struct virtqueue*) ; 

__attribute__((used)) static int get_free_page_and_send(struct virtio_balloon *vb)
{
	struct virtqueue *vq = vb->free_page_vq;
	struct page *page;
	struct scatterlist sg;
	int err, unused;
	void *p;

	/* Detach all the used buffers from the vq */
	while (virtqueue_get_buf(vq, &unused))
		;

	page = alloc_pages(VIRTIO_BALLOON_FREE_PAGE_ALLOC_FLAG,
			   VIRTIO_BALLOON_FREE_PAGE_ORDER);
	/*
	 * When the allocation returns NULL, it indicates that we have got all
	 * the possible free pages, so return -EINTR to stop.
	 */
	if (!page)
		return -EINTR;

	p = page_address(page);
	sg_init_one(&sg, p, VIRTIO_BALLOON_FREE_PAGE_SIZE);
	/* There is always 1 entry reserved for the cmd id to use. */
	if (vq->num_free > 1) {
		err = virtqueue_add_inbuf(vq, &sg, 1, p, GFP_KERNEL);
		if (unlikely(err)) {
			free_pages((unsigned long)p,
				   VIRTIO_BALLOON_FREE_PAGE_ORDER);
			return err;
		}
		virtqueue_kick(vq);
		spin_lock_irq(&vb->free_page_list_lock);
		balloon_page_push(&vb->free_page_list, page);
		vb->num_free_page_blocks++;
		spin_unlock_irq(&vb->free_page_list_lock);
	} else {
		/*
		 * The vq has no available entry to add this page block, so
		 * just free it.
		 */
		free_pages((unsigned long)p, VIRTIO_BALLOON_FREE_PAGE_ORDER);
	}

	return 0;
}
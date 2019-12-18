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
struct urb_node {int /*<<< orphan*/  entry; struct urb* urb; struct dlfb_data* dlfb; } ;
struct urb {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_2__ {size_t size; size_t count; scalar_t__ available; int /*<<< orphan*/  limit_sem; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct dlfb_data {TYPE_1__ urbs; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  dlfb_free_urb_list (struct dlfb_data*) ; 
 int /*<<< orphan*/  dlfb_urb_completion ; 
 int /*<<< orphan*/  kfree (struct urb_node*) ; 
 struct urb_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 char* usb_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,struct urb_node*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dlfb_alloc_urb_list(struct dlfb_data *dlfb, int count, size_t size)
{
	struct urb *urb;
	struct urb_node *unode;
	char *buf;
	size_t wanted_size = count * size;

	spin_lock_init(&dlfb->urbs.lock);

retry:
	dlfb->urbs.size = size;
	INIT_LIST_HEAD(&dlfb->urbs.list);

	sema_init(&dlfb->urbs.limit_sem, 0);
	dlfb->urbs.count = 0;
	dlfb->urbs.available = 0;

	while (dlfb->urbs.count * size < wanted_size) {
		unode = kzalloc(sizeof(*unode), GFP_KERNEL);
		if (!unode)
			break;
		unode->dlfb = dlfb;

		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!urb) {
			kfree(unode);
			break;
		}
		unode->urb = urb;

		buf = usb_alloc_coherent(dlfb->udev, size, GFP_KERNEL,
					 &urb->transfer_dma);
		if (!buf) {
			kfree(unode);
			usb_free_urb(urb);
			if (size > PAGE_SIZE) {
				size /= 2;
				dlfb_free_urb_list(dlfb);
				goto retry;
			}
			break;
		}

		/* urb->transfer_buffer_length set to actual before submit */
		usb_fill_bulk_urb(urb, dlfb->udev, usb_sndbulkpipe(dlfb->udev, 1),
			buf, size, dlfb_urb_completion, unode);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

		list_add_tail(&unode->entry, &dlfb->urbs.list);

		up(&dlfb->urbs.limit_sem);
		dlfb->urbs.count++;
		dlfb->urbs.available++;
	}

	return dlfb->urbs.count;
}
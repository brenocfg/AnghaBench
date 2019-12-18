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
struct urb_node {int /*<<< orphan*/  entry; struct urb* urb; int /*<<< orphan*/  release_urb_work; struct udl_device* dev; } ;
struct urb {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_2__ {size_t size; size_t count; scalar_t__ available; int /*<<< orphan*/  limit_sem; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct udl_device {TYPE_1__ urbs; int /*<<< orphan*/  udev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,size_t,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  kfree (struct urb_node*) ; 
 struct urb_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct udl_device* to_udl (struct drm_device*) ; 
 int /*<<< orphan*/  udl_free_urb_list (struct drm_device*) ; 
 int /*<<< orphan*/  udl_release_urb_work ; 
 int /*<<< orphan*/  udl_urb_completion ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 char* usb_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,struct urb_node*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int udl_alloc_urb_list(struct drm_device *dev, int count, size_t size)
{
	struct udl_device *udl = to_udl(dev);
	struct urb *urb;
	struct urb_node *unode;
	char *buf;
	size_t wanted_size = count * size;

	spin_lock_init(&udl->urbs.lock);

retry:
	udl->urbs.size = size;
	INIT_LIST_HEAD(&udl->urbs.list);

	sema_init(&udl->urbs.limit_sem, 0);
	udl->urbs.count = 0;
	udl->urbs.available = 0;

	while (udl->urbs.count * size < wanted_size) {
		unode = kzalloc(sizeof(struct urb_node), GFP_KERNEL);
		if (!unode)
			break;
		unode->dev = udl;

		INIT_DELAYED_WORK(&unode->release_urb_work,
			  udl_release_urb_work);

		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!urb) {
			kfree(unode);
			break;
		}
		unode->urb = urb;

		buf = usb_alloc_coherent(udl->udev, size, GFP_KERNEL,
					 &urb->transfer_dma);
		if (!buf) {
			kfree(unode);
			usb_free_urb(urb);
			if (size > PAGE_SIZE) {
				size /= 2;
				udl_free_urb_list(dev);
				goto retry;
			}
			break;
		}

		/* urb->transfer_buffer_length set to actual before submit */
		usb_fill_bulk_urb(urb, udl->udev, usb_sndbulkpipe(udl->udev, 1),
			buf, size, udl_urb_completion, unode);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

		list_add_tail(&unode->entry, &udl->urbs.list);

		up(&udl->urbs.limit_sem);
		udl->urbs.count++;
		udl->urbs.available++;
	}

	DRM_DEBUG("allocated %d %d byte urbs\n", udl->urbs.count, (int) size);

	return udl->urbs.count;
}
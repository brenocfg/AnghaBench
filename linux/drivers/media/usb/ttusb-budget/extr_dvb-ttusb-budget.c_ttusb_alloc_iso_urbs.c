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
struct urb {int dummy; } ;
struct ttusb {struct urb** iso_urb; int /*<<< orphan*/  iso_buffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FRAMES_PER_ISO_BUF ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ISO_BUF_COUNT ; 
 int /*<<< orphan*/  ISO_FRAME_SIZE ; 
 int /*<<< orphan*/  kcalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttusb_free_iso_urbs (struct ttusb*) ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttusb_alloc_iso_urbs(struct ttusb *ttusb)
{
	int i;

	ttusb->iso_buffer = kcalloc(FRAMES_PER_ISO_BUF * ISO_BUF_COUNT,
			ISO_FRAME_SIZE, GFP_KERNEL);
	if (!ttusb->iso_buffer)
		return -ENOMEM;

	for (i = 0; i < ISO_BUF_COUNT; i++) {
		struct urb *urb;

		if (!
		    (urb =
		     usb_alloc_urb(FRAMES_PER_ISO_BUF, GFP_ATOMIC))) {
			ttusb_free_iso_urbs(ttusb);
			return -ENOMEM;
		}

		ttusb->iso_urb[i] = urb;
	}

	return 0;
}
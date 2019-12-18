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
struct usb_tx {struct usb_tx* buf; int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct usb_tx*) ; 
 struct usb_tx* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct usb_tx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_tx *alloc_tx_struct(int len)
{
	struct usb_tx *t = NULL;
	int ret = 0;

	t = kzalloc(sizeof(*t), GFP_ATOMIC);
	if (!t) {
		ret = -ENOMEM;
		goto out;
	}

	t->urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!(len % 512))
		len++;

	t->buf = kmalloc(len, GFP_ATOMIC);
	if (!t->urb || !t->buf) {
		ret = -ENOMEM;
		goto out;
	}

out:
	if (ret < 0) {
		if (t) {
			usb_free_urb(t->urb);
			kfree(t->buf);
			kfree(t);
		}
		return NULL;
	}

	return t;
}
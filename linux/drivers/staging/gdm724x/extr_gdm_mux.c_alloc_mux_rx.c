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
struct mux_rx {struct mux_rx* buf; int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MUX_RX_MAX_SIZE ; 
 int /*<<< orphan*/  kfree (struct mux_rx*) ; 
 struct mux_rx* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mux_rx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mux_rx *alloc_mux_rx(void)
{
	struct mux_rx *r;

	r = kzalloc(sizeof(*r), GFP_KERNEL);
	if (!r)
		return NULL;

	r->urb = usb_alloc_urb(0, GFP_KERNEL);
	r->buf = kmalloc(MUX_RX_MAX_SIZE, GFP_KERNEL);
	if (!r->urb || !r->buf) {
		usb_free_urb(r->urb);
		kfree(r->buf);
		kfree(r);
		return NULL;
	}

	return r;
}
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
struct mux_tx {struct mux_tx* buf; int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MUX_TX_MAX_SIZE ; 
 int /*<<< orphan*/  kfree (struct mux_tx*) ; 
 struct mux_tx* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mux_tx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mux_tx *alloc_mux_tx(int len)
{
	struct mux_tx *t;

	t = kzalloc(sizeof(*t), GFP_ATOMIC);
	if (!t)
		return NULL;

	t->urb = usb_alloc_urb(0, GFP_ATOMIC);
	t->buf = kmalloc(MUX_TX_MAX_SIZE, GFP_ATOMIC);
	if (!t->urb || !t->buf) {
		usb_free_urb(t->urb);
		kfree(t->buf);
		kfree(t);
		return NULL;
	}

	return t;
}
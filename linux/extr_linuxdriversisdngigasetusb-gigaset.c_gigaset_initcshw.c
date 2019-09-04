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
struct usb_cardstate {int* bchars; int /*<<< orphan*/ * read_urb; int /*<<< orphan*/ * bulk_out_urb; int /*<<< orphan*/ * bulk_out_buffer; } ;
struct TYPE_2__ {struct usb_cardstate* usb; } ;
struct cardstate {int /*<<< orphan*/  write_tasklet; TYPE_1__ hw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gigaset_modem_fill ; 
 struct usb_cardstate* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int gigaset_initcshw(struct cardstate *cs)
{
	struct usb_cardstate *ucs;

	cs->hw.usb = ucs =
		kmalloc(sizeof(struct usb_cardstate), GFP_KERNEL);
	if (!ucs) {
		pr_err("out of memory\n");
		return -ENOMEM;
	}

	ucs->bchars[0] = 0;
	ucs->bchars[1] = 0;
	ucs->bchars[2] = 0;
	ucs->bchars[3] = 0;
	ucs->bchars[4] = 0x11;
	ucs->bchars[5] = 0x13;
	ucs->bulk_out_buffer = NULL;
	ucs->bulk_out_urb = NULL;
	ucs->read_urb = NULL;
	tasklet_init(&cs->write_tasklet,
		     gigaset_modem_fill, (unsigned long) cs);

	return 0;
}
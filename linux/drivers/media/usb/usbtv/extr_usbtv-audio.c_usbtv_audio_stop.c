#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ u16 ;
struct usbtv {TYPE_3__* snd_bulk_urb; } ;
struct TYPE_7__ {int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__ const**) ; 
#define  USBTV_BASE 128 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_3__*) ; 
 int /*<<< orphan*/  usbtv_set_regs (struct usbtv*,TYPE_1__ const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbtv_audio_stop(struct usbtv *chip)
{
	static const u16 setup[][2] = {
	/* The original windows driver sometimes sends also:
	 *   { USBTV_BASE + 0x00a2, 0x0013 }
	 * but it seems useless and its real effects are untested at
	 * the moment.
	 */
		{ USBTV_BASE + 0x027d, 0x0000 },
		{ USBTV_BASE + 0x0280, 0x0010 },
		{ USBTV_BASE + 0x0282, 0x0010 },
	};

	if (chip->snd_bulk_urb) {
		usb_kill_urb(chip->snd_bulk_urb);
		kfree(chip->snd_bulk_urb->transfer_buffer);
		usb_free_urb(chip->snd_bulk_urb);
		chip->snd_bulk_urb = NULL;
	}

	usbtv_set_regs(chip, setup, ARRAY_SIZE(setup));

	return 0;
}
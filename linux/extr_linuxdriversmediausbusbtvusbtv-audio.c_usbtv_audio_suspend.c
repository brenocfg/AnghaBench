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
struct usbtv {scalar_t__ snd_bulk_urb; int /*<<< orphan*/  snd_stream; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

void usbtv_audio_suspend(struct usbtv *usbtv)
{
	if (atomic_read(&usbtv->snd_stream) && usbtv->snd_bulk_urb)
		usb_kill_urb(usbtv->snd_bulk_urb);
}
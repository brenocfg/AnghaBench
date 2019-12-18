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
struct go7007_usb {int /*<<< orphan*/ * audio_urbs; int /*<<< orphan*/ * video_urbs; } ;
struct go7007 {scalar_t__ status; scalar_t__ audio_enabled; struct go7007_usb* hpi_context; } ;

/* Variables and functions */
 scalar_t__ STATUS_SHUTDOWN ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int go7007_usb_stream_stop(struct go7007 *go)
{
	struct go7007_usb *usb = go->hpi_context;
	int i;

	if (go->status == STATUS_SHUTDOWN)
		return 0;
	for (i = 0; i < 8; ++i)
		usb_kill_urb(usb->video_urbs[i]);
	if (go->audio_enabled)
		for (i = 0; i < 8; ++i)
			usb_kill_urb(usb->audio_urbs[i]);
	return 0;
}
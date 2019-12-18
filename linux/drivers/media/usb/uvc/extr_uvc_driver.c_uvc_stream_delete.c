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
struct TYPE_2__ {struct uvc_streaming* bmaControls; } ;
struct uvc_streaming {TYPE_1__ header; struct uvc_streaming* format; int /*<<< orphan*/  intf; int /*<<< orphan*/  mutex; scalar_t__ async_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct uvc_streaming*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_intf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uvc_stream_delete(struct uvc_streaming *stream)
{
	if (stream->async_wq)
		destroy_workqueue(stream->async_wq);

	mutex_destroy(&stream->mutex);

	usb_put_intf(stream->intf);

	kfree(stream->format);
	kfree(stream->header.bmaControls);
	kfree(stream);
}
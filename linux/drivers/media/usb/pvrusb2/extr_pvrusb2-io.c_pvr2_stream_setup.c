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
struct usb_device {int dummy; } ;
struct pvr2_stream {int endpoint; unsigned int fail_tolerance; int /*<<< orphan*/  mutex; struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_stream_internal_flush (struct pvr2_stream*) ; 

void pvr2_stream_setup(struct pvr2_stream *sp,
		       struct usb_device *dev,
		       int endpoint,
		       unsigned int tolerance)
{
	mutex_lock(&sp->mutex); do {
		pvr2_stream_internal_flush(sp);
		sp->dev = dev;
		sp->endpoint = endpoint;
		sp->fail_tolerance = tolerance;
	} while (0); mutex_unlock(&sp->mutex);
}
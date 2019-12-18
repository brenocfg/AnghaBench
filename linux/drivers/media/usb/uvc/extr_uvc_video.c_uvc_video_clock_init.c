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
struct uvc_clock {int size; int /*<<< orphan*/ * samples; int /*<<< orphan*/  lock; } ;
struct uvc_streaming {struct uvc_clock clock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_video_clock_reset (struct uvc_streaming*) ; 

__attribute__((used)) static int uvc_video_clock_init(struct uvc_streaming *stream)
{
	struct uvc_clock *clock = &stream->clock;

	spin_lock_init(&clock->lock);
	clock->size = 32;

	clock->samples = kmalloc_array(clock->size, sizeof(*clock->samples),
				       GFP_KERNEL);
	if (clock->samples == NULL)
		return -ENOMEM;

	uvc_video_clock_reset(stream);

	return 0;
}
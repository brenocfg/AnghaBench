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
struct v4l2_enum_dv_timings {size_t index; int /*<<< orphan*/  timings; int /*<<< orphan*/  reserved; } ;
struct hdpvr_fh {int legacy_mode; } ;
struct TYPE_2__ {scalar_t__ video_input; } ;
struct hdpvr_device {TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/ * hdpvr_dv_timings ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_enum_dv_timings(struct file *file, void *_fh,
				    struct v4l2_enum_dv_timings *timings)
{
	struct hdpvr_device *dev = video_drvdata(file);
	struct hdpvr_fh *fh = _fh;

	fh->legacy_mode = false;
	memset(timings->reserved, 0, sizeof(timings->reserved));
	if (dev->options.video_input)
		return -ENODATA;
	if (timings->index >= ARRAY_SIZE(hdpvr_dv_timings))
		return -EINVAL;
	timings->timings = hdpvr_dv_timings[timings->index];
	return 0;
}
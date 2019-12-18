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
struct video_device {int dummy; } ;
struct file {int dummy; } ;
struct cx18_stream {struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  serialize_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_ERR (char*,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 scalar_t__ cx18_init_on_first_open (struct cx18*) ; 
 int cx18_serialized_open (struct cx18_stream*,struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 struct cx18_stream* video_get_drvdata (struct video_device*) ; 

int cx18_v4l2_open(struct file *filp)
{
	int res;
	struct video_device *video_dev = video_devdata(filp);
	struct cx18_stream *s = video_get_drvdata(video_dev);
	struct cx18 *cx = s->cx;

	mutex_lock(&cx->serialize_lock);
	if (cx18_init_on_first_open(cx)) {
		CX18_ERR("Failed to initialize on %s\n",
			 video_device_node_name(video_dev));
		mutex_unlock(&cx->serialize_lock);
		return -ENXIO;
	}
	res = cx18_serialized_open(s, filp);
	mutex_unlock(&cx->serialize_lock);
	return res;
}
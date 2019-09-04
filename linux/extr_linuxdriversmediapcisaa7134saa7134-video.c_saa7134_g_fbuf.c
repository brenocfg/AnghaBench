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
struct v4l2_framebuffer {int /*<<< orphan*/  capability; } ;
struct saa7134_dev {struct v4l2_framebuffer ovbuf; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FBUF_CAP_LIST_CLIPPING ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int saa7134_g_fbuf(struct file *file, void *f,
				struct v4l2_framebuffer *fb)
{
	struct saa7134_dev *dev = video_drvdata(file);

	*fb = dev->ovbuf;
	fb->capability = V4L2_FBUF_CAP_LIST_CLIPPING;

	return 0;
}
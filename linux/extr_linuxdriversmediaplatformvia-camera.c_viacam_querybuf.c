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
struct via_camera {int /*<<< orphan*/  vb_queue; } ;
struct v4l2_buffer {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int videobuf_querybuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

__attribute__((used)) static int viacam_querybuf(struct file *filp, void *priv,
		struct v4l2_buffer *buf)
{
	struct via_camera *cam = priv;

	return videobuf_querybuf(&cam->vb_queue, buf);
}
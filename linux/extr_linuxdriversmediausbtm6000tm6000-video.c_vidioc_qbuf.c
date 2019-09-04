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
struct v4l2_buffer {int dummy; } ;
struct tm6000_fh {int /*<<< orphan*/  vb_vidq; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int videobuf_qbuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

__attribute__((used)) static int vidioc_qbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	struct tm6000_fh  *fh = priv;

	return videobuf_qbuf(&fh->vb_vidq, p);
}
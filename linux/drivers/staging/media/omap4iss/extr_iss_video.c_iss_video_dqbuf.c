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
struct iss_video_fh {int /*<<< orphan*/  queue; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 struct iss_video_fh* to_iss_video_fh (void*) ; 
 int vb2_dqbuf (int /*<<< orphan*/ *,struct v4l2_buffer*,int) ; 

__attribute__((used)) static int
iss_video_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
	struct iss_video_fh *vfh = to_iss_video_fh(fh);

	return vb2_dqbuf(&vfh->queue, b, file->f_flags & O_NONBLOCK);
}
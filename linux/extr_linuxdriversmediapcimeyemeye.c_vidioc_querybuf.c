#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int offset; } ;
struct v4l2_buffer {unsigned int index; int flags; unsigned int length; TYPE_2__ m; int /*<<< orphan*/  memory; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  field; int /*<<< orphan*/  bytesused; } ;
struct file {int dummy; } ;
struct TYPE_6__ {TYPE_1__* grab_buffer; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEYE_BUF_DONE ; 
 scalar_t__ MEYE_BUF_USING ; 
 int V4L2_BUF_FLAG_DONE ; 
 int V4L2_BUF_FLAG_MAPPED ; 
 int V4L2_BUF_FLAG_QUEUED ; 
 int V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 unsigned int gbuffers ; 
 unsigned int gbufsize ; 
 TYPE_3__ meye ; 

__attribute__((used)) static int vidioc_querybuf(struct file *file, void *fh, struct v4l2_buffer *buf)
{
	unsigned int index = buf->index;

	if (index >= gbuffers)
		return -EINVAL;

	buf->bytesused = meye.grab_buffer[index].size;
	buf->flags = V4L2_BUF_FLAG_MAPPED | V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;

	if (meye.grab_buffer[index].state == MEYE_BUF_USING)
		buf->flags |= V4L2_BUF_FLAG_QUEUED;

	if (meye.grab_buffer[index].state == MEYE_BUF_DONE)
		buf->flags |= V4L2_BUF_FLAG_DONE;

	buf->field = V4L2_FIELD_NONE;
	buf->timestamp = meye.grab_buffer[index].timestamp;
	buf->sequence = meye.grab_buffer[index].sequence;
	buf->memory = V4L2_MEMORY_MMAP;
	buf->m.offset = index * gbufsize;
	buf->length = gbufsize;

	return 0;
}
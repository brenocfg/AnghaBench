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
struct vm_area_struct {int dummy; } ;
struct file {struct cx18_open_id* private_data; } ;
struct cx18_stream {scalar_t__ vb_type; int /*<<< orphan*/  vbuf_q; int /*<<< orphan*/  name; int /*<<< orphan*/  s_flags; } ;
struct cx18_open_id {size_t type; struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  serialize_lock; struct cx18_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_FILE (char*) ; 
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,int /*<<< orphan*/ ,int) ; 
 size_t CX18_ENC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  CX18_F_S_STREAMING ; 
 int /*<<< orphan*/  CX18_F_S_STREAMOFF ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int cx18_start_capture (struct cx18_open_id*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int videobuf_mmap_mapper (int /*<<< orphan*/ *,struct vm_area_struct*) ; 

int cx18_v4l2_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct cx18_open_id *id = file->private_data;
	struct cx18 *cx = id->cx;
	struct cx18_stream *s = &cx->streams[id->type];
	int eof = test_bit(CX18_F_S_STREAMOFF, &s->s_flags);

	if ((s->vb_type == V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(id->type == CX18_ENC_STREAM_TYPE_YUV)) {

		/* Start a capture if there is none */
		if (!eof && !test_bit(CX18_F_S_STREAMING, &s->s_flags)) {
			int rc;

			mutex_lock(&cx->serialize_lock);
			rc = cx18_start_capture(id);
			mutex_unlock(&cx->serialize_lock);
			if (rc) {
				CX18_DEBUG_INFO(
					"Could not start capture for %s (%d)\n",
					s->name, rc);
				return -EINVAL;
			}
			CX18_DEBUG_FILE("Encoder mmap started capture\n");
		}

		return videobuf_mmap_mapper(&s->vbuf_q, vma);
	}

	return -EINVAL;
}
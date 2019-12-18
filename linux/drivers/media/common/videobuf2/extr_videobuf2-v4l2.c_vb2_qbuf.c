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
struct vb2_queue {int dummy; } ;
struct v4l2_buffer {int /*<<< orphan*/  index; } ;
struct media_request {int dummy; } ;
struct media_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  media_request_put (struct media_request*) ; 
 int vb2_core_qbuf (struct vb2_queue*,int /*<<< orphan*/ ,struct v4l2_buffer*,struct media_request*) ; 
 scalar_t__ vb2_fileio_is_active (struct vb2_queue*) ; 
 int vb2_queue_or_prepare_buf (struct vb2_queue*,struct media_device*,struct v4l2_buffer*,int,struct media_request**) ; 

int vb2_qbuf(struct vb2_queue *q, struct media_device *mdev,
	     struct v4l2_buffer *b)
{
	struct media_request *req = NULL;
	int ret;

	if (vb2_fileio_is_active(q)) {
		dprintk(1, "file io in progress\n");
		return -EBUSY;
	}

	ret = vb2_queue_or_prepare_buf(q, mdev, b, false, &req);
	if (ret)
		return ret;
	ret = vb2_core_qbuf(q, b->index, b, req);
	if (req)
		media_request_put(req);
	return ret;
}
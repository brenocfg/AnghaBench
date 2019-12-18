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
struct vb2_buffer {int dummy; } ;
struct amvdec_session {int /*<<< orphan*/  bufs_recycle_lock; int /*<<< orphan*/  bufs_recycle; } ;
struct amvdec_buffer {int /*<<< orphan*/  list; struct vb2_buffer* vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct amvdec_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vdec_queue_recycle(struct amvdec_session *sess, struct vb2_buffer *vb)
{
	struct amvdec_buffer *new_buf;

	new_buf = kmalloc(sizeof(*new_buf), GFP_KERNEL);
	new_buf->vb = vb;

	mutex_lock(&sess->bufs_recycle_lock);
	list_add_tail(&new_buf->list, &sess->bufs_recycle);
	mutex_unlock(&sess->bufs_recycle_lock);
}
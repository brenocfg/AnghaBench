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
struct vip_buffer {int /*<<< orphan*/  list; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct sta2x11_vip {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct vip_buffer* to_vip_buffer (struct vb2_v4l2_buffer*) ; 
 struct sta2x11_vip* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_streaming (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vip_active_buf_next (struct sta2x11_vip*) ; 

__attribute__((used)) static void buffer_finish(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct sta2x11_vip *vip = vb2_get_drv_priv(vb->vb2_queue);
	struct vip_buffer *vip_buf = to_vip_buffer(vbuf);

	/* Buffer handled, remove it from the list */
	spin_lock(&vip->lock);
	list_del_init(&vip_buf->list);
	spin_unlock(&vip->lock);

	if (vb2_is_streaming(vb->vb2_queue))
		vip_active_buf_next(vip);
}
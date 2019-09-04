#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct tw686x_video_channel {int width; int height; TYPE_1__* format; } ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 int EINVAL ; 
 struct tw686x_video_channel* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 unsigned int vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int tw686x_buf_prepare(struct vb2_buffer *vb)
{
	struct tw686x_video_channel *vc = vb2_get_drv_priv(vb->vb2_queue);
	unsigned int size =
		(vc->width * vc->height * vc->format->depth) >> 3;

	if (vb2_plane_size(vb, 0) < size)
		return -EINVAL;
	vb2_set_plane_payload(vb, 0, size);
	return 0;
}
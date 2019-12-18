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
struct via_camera {int /*<<< orphan*/  buffer_queue; } ;
struct via_buffer {int /*<<< orphan*/  queue; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct via_camera* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 struct via_buffer* vb2_to_via_buffer (struct vb2_buffer*) ; 

__attribute__((used)) static void viacam_vb2_queue(struct vb2_buffer *vb)
{
	struct via_camera *cam = vb2_get_drv_priv(vb->vb2_queue);
	struct via_buffer *via = vb2_to_via_buffer(vb);

	list_add_tail(&via->queue, &cam->buffer_queue);
}
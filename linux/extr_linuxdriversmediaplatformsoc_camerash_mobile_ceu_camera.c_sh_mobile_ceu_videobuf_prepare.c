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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int dummy; } ;
struct sh_mobile_ceu_buffer {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,struct vb2_buffer*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct sh_mobile_ceu_buffer* to_ceu_vb (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 

__attribute__((used)) static int sh_mobile_ceu_videobuf_prepare(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct sh_mobile_ceu_buffer *buf = to_ceu_vb(vbuf);

	/* Added list head initialization on alloc */
	WARN(!list_empty(&buf->queue), "Buffer %p on queue!\n", vb);

	return 0;
}
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
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct sh_veu_dev {int /*<<< orphan*/  m2m_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  sh_veu_process (struct sh_veu_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_veu_device_run(void *priv)
{
	struct sh_veu_dev *veu = priv;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;

	src_buf = v4l2_m2m_next_src_buf(veu->m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(veu->m2m_ctx);

	if (src_buf && dst_buf)
		sh_veu_process(veu, &src_buf->vb2_buf, &dst_buf->vb2_buf);
}
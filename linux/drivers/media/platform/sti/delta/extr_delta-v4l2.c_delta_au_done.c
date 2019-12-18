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
struct vb2_v4l2_buffer {scalar_t__ sequence; } ;
struct delta_ctx {int /*<<< orphan*/  au_num; } ;
struct delta_au {struct vb2_v4l2_buffer vbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delta_au_done(struct delta_ctx *ctx, struct delta_au *au, int err)
{
	struct vb2_v4l2_buffer *vbuf;

	vbuf = &au->vbuf;
	vbuf->sequence = ctx->au_num++;
	v4l2_m2m_buf_done(vbuf, err ? VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
}
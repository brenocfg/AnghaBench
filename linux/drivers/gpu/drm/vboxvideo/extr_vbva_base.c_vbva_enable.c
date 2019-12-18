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
struct vbva_buffer {int partial_write_tresh; scalar_t__ data_len; } ;
struct vbva_buf_ctx {struct vbva_buffer* vbva; scalar_t__ buffer_length; } ;
struct gen_pool {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vbva_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vbva_disable (struct vbva_buf_ctx*,struct gen_pool*,int /*<<< orphan*/ ) ; 
 int vbva_inform_host (struct vbva_buf_ctx*,struct gen_pool*,int /*<<< orphan*/ ,int) ; 

bool vbva_enable(struct vbva_buf_ctx *vbva_ctx, struct gen_pool *ctx,
		 struct vbva_buffer *vbva, s32 screen)
{
	bool ret = false;

	memset(vbva, 0, sizeof(*vbva));
	vbva->partial_write_tresh = 256;
	vbva->data_len = vbva_ctx->buffer_length - sizeof(struct vbva_buffer);
	vbva_ctx->vbva = vbva;

	ret = vbva_inform_host(vbva_ctx, ctx, screen, true);
	if (!ret)
		vbva_disable(vbva_ctx, ctx, screen);

	return ret;
}
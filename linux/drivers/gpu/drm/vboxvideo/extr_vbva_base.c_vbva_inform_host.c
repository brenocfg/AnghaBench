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
struct TYPE_2__ {int flags; scalar_t__ result; int /*<<< orphan*/  offset; } ;
struct vbva_enable_ex {TYPE_1__ base; scalar_t__ screen_id; } ;
struct vbva_buf_ctx {int /*<<< orphan*/  buffer_offset; } ;
struct gen_pool {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  HGSMI_CH_VBVA ; 
 int /*<<< orphan*/  VBVA_ENABLE ; 
 int VBVA_F_ABSOFFSET ; 
 int VBVA_F_DISABLE ; 
 int VBVA_F_ENABLE ; 
 int VBVA_F_EXTENDED ; 
 scalar_t__ VERR_NOT_SUPPORTED ; 
 struct vbva_enable_ex* hgsmi_buffer_alloc (struct gen_pool*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hgsmi_buffer_free (struct gen_pool*,struct vbva_enable_ex*) ; 
 int /*<<< orphan*/  hgsmi_buffer_submit (struct gen_pool*,struct vbva_enable_ex*) ; 

__attribute__((used)) static bool vbva_inform_host(struct vbva_buf_ctx *vbva_ctx,
			     struct gen_pool *ctx, s32 screen, bool enable)
{
	struct vbva_enable_ex *p;
	bool ret;

	p = hgsmi_buffer_alloc(ctx, sizeof(*p), HGSMI_CH_VBVA, VBVA_ENABLE);
	if (!p)
		return false;

	p->base.flags = enable ? VBVA_F_ENABLE : VBVA_F_DISABLE;
	p->base.offset = vbva_ctx->buffer_offset;
	p->base.result = VERR_NOT_SUPPORTED;
	if (screen >= 0) {
		p->base.flags |= VBVA_F_EXTENDED | VBVA_F_ABSOFFSET;
		p->screen_id = screen;
	}

	hgsmi_buffer_submit(ctx, p);

	if (enable)
		ret = p->base.result >= 0;
	else
		ret = true;

	hgsmi_buffer_free(ctx, p);

	return ret;
}
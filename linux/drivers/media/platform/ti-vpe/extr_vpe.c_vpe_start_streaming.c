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
struct vpe_ctx {scalar_t__ sequence; scalar_t__ deinterlacing; int /*<<< orphan*/  dev; } ;
struct vb2_queue {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 scalar_t__ check_srcdst_sizes (struct vpe_ctx*) ; 
 int /*<<< orphan*/  config_edi_input_mode (struct vpe_ctx*,int) ; 
 int /*<<< orphan*/  set_srcdst_params (struct vpe_ctx*) ; 
 struct vpe_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vpe_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vpe_return_all_buffers (struct vpe_ctx*,struct vb2_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpe_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct vpe_ctx *ctx = vb2_get_drv_priv(q);

	/* Check any of the size exceed maximum scaling sizes */
	if (check_srcdst_sizes(ctx)) {
		vpe_err(ctx->dev,
			"Conversion setup failed, check source and destination parameters\n"
			);
		vpe_return_all_buffers(ctx, q, VB2_BUF_STATE_QUEUED);
		return -EINVAL;
	}

	if (ctx->deinterlacing)
		config_edi_input_mode(ctx, 0x0);

	if (ctx->sequence != 0)
		set_srcdst_params(ctx);

	return 0;
}
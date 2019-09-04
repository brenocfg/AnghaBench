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
struct delta_mjpeg_ctx {int /*<<< orphan*/ * ipc_hdl; } ;
struct delta_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  delta_ipc_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct delta_mjpeg_ctx*) ; 
 struct delta_mjpeg_ctx* to_ctx (struct delta_ctx*) ; 

__attribute__((used)) static int delta_mjpeg_close(struct delta_ctx *pctx)
{
	struct delta_mjpeg_ctx *ctx = to_ctx(pctx);

	if (ctx->ipc_hdl) {
		delta_ipc_close(ctx->ipc_hdl);
		ctx->ipc_hdl = NULL;
	}

	kfree(ctx);

	return 0;
}
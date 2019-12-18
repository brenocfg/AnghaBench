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
struct coda_ctx {int /*<<< orphan*/  ctrls; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_JPEG_COMPRESSION_QUALITY ; 
 int /*<<< orphan*/  V4L2_CID_JPEG_RESTART_INTERVAL ; 
 int /*<<< orphan*/  coda_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void coda_jpeg_encode_ctrls(struct coda_ctx *ctx)
{
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_JPEG_COMPRESSION_QUALITY, 5, 100, 1, 50);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_JPEG_RESTART_INTERVAL, 0, 100, 1, 0);
}
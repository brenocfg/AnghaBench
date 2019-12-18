#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipu_csc_scaler_priv {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct ipu_csc_scaler_ctx {TYPE_1__ fh; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct ipu_csc_scaler_ctx*) ; 
 struct ipu_csc_scaler_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipu_csc_scaler_ctx*) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct ipu_csc_scaler_priv* video_drvdata (struct file*) ; 

__attribute__((used)) static int ipu_csc_scaler_release(struct file *file)
{
	struct ipu_csc_scaler_priv *priv = video_drvdata(file);
	struct ipu_csc_scaler_ctx *ctx = fh_to_ctx(file->private_data);

	dev_dbg(priv->dev, "Releasing instance %p\n", ctx);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	kfree(ctx);

	return 0;
}
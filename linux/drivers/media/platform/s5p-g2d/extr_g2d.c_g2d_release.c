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
struct g2d_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct g2d_ctx {int /*<<< orphan*/  fh; int /*<<< orphan*/  ctrl_handler; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 struct g2d_ctx* fh2ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct g2d_ctx*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*) ; 
 struct g2d_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int g2d_release(struct file *file)
{
	struct g2d_dev *dev = video_drvdata(file);
	struct g2d_ctx *ctx = fh2ctx(file->private_data);

	v4l2_ctrl_handler_free(&ctx->ctrl_handler);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	kfree(ctx);
	v4l2_info(&dev->v4l2_dev, "instance closed\n");
	return 0;
}
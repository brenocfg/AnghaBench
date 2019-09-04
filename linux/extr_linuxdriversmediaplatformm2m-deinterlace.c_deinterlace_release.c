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
struct file {struct deinterlace_ctx* private_data; } ;
struct deinterlace_dev {int dummy; } ;
struct deinterlace_ctx {struct deinterlace_ctx* xt; int /*<<< orphan*/  m2m_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct deinterlace_dev*,char*,struct deinterlace_ctx*) ; 
 int /*<<< orphan*/  kfree (struct deinterlace_ctx*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct deinterlace_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int deinterlace_release(struct file *file)
{
	struct deinterlace_dev *pcdev = video_drvdata(file);
	struct deinterlace_ctx *ctx = file->private_data;

	dprintk(pcdev, "Releasing instance %p\n", ctx);

	v4l2_m2m_ctx_release(ctx->m2m_ctx);
	kfree(ctx->xt);
	kfree(ctx);

	return 0;
}
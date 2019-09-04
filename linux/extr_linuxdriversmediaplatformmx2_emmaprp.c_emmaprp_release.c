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
struct file {struct emmaprp_ctx* private_data; } ;
struct emmaprp_dev {int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  clk_emma_ipg; int /*<<< orphan*/  clk_emma_ahb; } ;
struct emmaprp_ctx {int /*<<< orphan*/  m2m_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (struct emmaprp_dev*,char*,struct emmaprp_ctx*) ; 
 int /*<<< orphan*/  kfree (struct emmaprp_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct emmaprp_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int emmaprp_release(struct file *file)
{
	struct emmaprp_dev *pcdev = video_drvdata(file);
	struct emmaprp_ctx *ctx = file->private_data;

	dprintk(pcdev, "Releasing instance %p\n", ctx);

	mutex_lock(&pcdev->dev_mutex);
	clk_disable_unprepare(pcdev->clk_emma_ahb);
	clk_disable_unprepare(pcdev->clk_emma_ipg);
	v4l2_m2m_ctx_release(ctx->m2m_ctx);
	mutex_unlock(&pcdev->dev_mutex);
	kfree(ctx);

	return 0;
}
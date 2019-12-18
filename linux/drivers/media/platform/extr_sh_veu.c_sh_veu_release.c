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
struct sh_veu_file {int /*<<< orphan*/  fh; } ;
struct sh_veu_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * m2m_ctx; struct sh_veu_file* capture; struct sh_veu_file* output; } ;
struct file {struct sh_veu_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct sh_veu_file*) ; 
 int /*<<< orphan*/  kfree (struct sh_veu_file*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_get_vq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ ) ; 
 struct sh_veu_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int sh_veu_release(struct file *file)
{
	struct sh_veu_dev *veu = video_drvdata(file);
	struct sh_veu_file *veu_file = file->private_data;

	dev_dbg(veu->dev, "Releasing instance %p\n", veu_file);

	if (veu_file == veu->capture) {
		veu->capture = NULL;
		vb2_queue_release(v4l2_m2m_get_vq(veu->m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE));
	}

	if (veu_file == veu->output) {
		veu->output = NULL;
		vb2_queue_release(v4l2_m2m_get_vq(veu->m2m_ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT));
	}

	if (!veu->output && !veu->capture && veu->m2m_ctx) {
		v4l2_m2m_ctx_release(veu->m2m_ctx);
		veu->m2m_ctx = NULL;
	}

	pm_runtime_put(veu->dev);
	v4l2_fh_del(&veu_file->fh);
	v4l2_fh_exit(&veu_file->fh);

	kfree(veu_file);

	return 0;
}
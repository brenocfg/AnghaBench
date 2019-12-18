#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct file {TYPE_3__* private_data; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  m2m_ctx; int /*<<< orphan*/ * ctrl_handler; } ;
struct TYPE_6__ {int numerator; int denominator; } ;
struct amvdec_session {int width; int height; int /*<<< orphan*/  m2m_dev; TYPE_3__ fh; int /*<<< orphan*/  m2m_ctx; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  ts_spinlock; int /*<<< orphan*/  bufs_recycle_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  esparser_queue_work; int /*<<< orphan*/  bufs_recycle; int /*<<< orphan*/  timestamps; TYPE_2__ pixelaspect; struct amvdec_format const* fmt_out; int /*<<< orphan*/  pixfmt_cap; struct amvdec_core* core; } ;
struct amvdec_format {int /*<<< orphan*/ * pixfmts_cap; } ;
struct amvdec_core {int /*<<< orphan*/  vdev_dec; TYPE_1__* platform; struct device* dev; } ;
struct TYPE_5__ {struct amvdec_format* formats; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  esparser_queue_all_src ; 
 int /*<<< orphan*/  kfree (struct amvdec_session*) ; 
 struct amvdec_session* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m2m_queue_init ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct amvdec_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int vdec_init_ctrls (struct amvdec_session*) ; 
 int /*<<< orphan*/  vdec_m2m_ops ; 
 struct amvdec_core* video_drvdata (struct file*) ; 

__attribute__((used)) static int vdec_open(struct file *file)
{
	struct amvdec_core *core = video_drvdata(file);
	struct device *dev = core->dev;
	const struct amvdec_format *formats = core->platform->formats;
	struct amvdec_session *sess;
	int ret;

	sess = kzalloc(sizeof(*sess), GFP_KERNEL);
	if (!sess)
		return -ENOMEM;

	sess->core = core;

	sess->m2m_dev = v4l2_m2m_init(&vdec_m2m_ops);
	if (IS_ERR(sess->m2m_dev)) {
		dev_err(dev, "Fail to v4l2_m2m_init\n");
		ret = PTR_ERR(sess->m2m_dev);
		goto err_free_sess;
	}

	sess->m2m_ctx = v4l2_m2m_ctx_init(sess->m2m_dev, sess, m2m_queue_init);
	if (IS_ERR(sess->m2m_ctx)) {
		dev_err(dev, "Fail to v4l2_m2m_ctx_init\n");
		ret = PTR_ERR(sess->m2m_ctx);
		goto err_m2m_release;
	}

	ret = vdec_init_ctrls(sess);
	if (ret)
		goto err_m2m_release;

	sess->pixfmt_cap = formats[0].pixfmts_cap[0];
	sess->fmt_out = &formats[0];
	sess->width = 1280;
	sess->height = 720;
	sess->pixelaspect.numerator = 1;
	sess->pixelaspect.denominator = 1;

	INIT_LIST_HEAD(&sess->timestamps);
	INIT_LIST_HEAD(&sess->bufs_recycle);
	INIT_WORK(&sess->esparser_queue_work, esparser_queue_all_src);
	mutex_init(&sess->lock);
	mutex_init(&sess->bufs_recycle_lock);
	spin_lock_init(&sess->ts_spinlock);

	v4l2_fh_init(&sess->fh, core->vdev_dec);
	sess->fh.ctrl_handler = &sess->ctrl_handler;
	v4l2_fh_add(&sess->fh);
	sess->fh.m2m_ctx = sess->m2m_ctx;
	file->private_data = &sess->fh;

	return 0;

err_m2m_release:
	v4l2_m2m_release(sess->m2m_dev);
err_free_sess:
	kfree(sess);
	return ret;
}
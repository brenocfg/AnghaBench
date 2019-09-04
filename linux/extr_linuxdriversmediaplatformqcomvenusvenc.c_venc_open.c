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
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; int /*<<< orphan*/ * ctrl_handler; } ;
struct venus_inst {int /*<<< orphan*/  m2m_dev; TYPE_1__ fh; int /*<<< orphan*/  m2m_ctx; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  session_type; struct venus_core* core; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; int /*<<< orphan*/  internalbufs; int /*<<< orphan*/  registeredbufs; int /*<<< orphan*/  dpbbufs; } ;
struct venus_core {int /*<<< orphan*/  dev_enc; int /*<<< orphan*/  vdev_enc; } ;
struct file {TYPE_1__* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDC_SESSION_TYPE_ENC ; 
 int hfi_session_create (struct venus_inst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi_session_destroy (struct venus_inst*) ; 
 int /*<<< orphan*/  kfree (struct venus_inst*) ; 
 struct venus_inst* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m2m_queue_init ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct venus_inst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_ctrl_deinit (struct venus_inst*) ; 
 int venc_ctrl_init (struct venus_inst*) ; 
 int /*<<< orphan*/  venc_hfi_ops ; 
 int /*<<< orphan*/  venc_inst_init (struct venus_inst*) ; 
 int /*<<< orphan*/  venc_m2m_ops ; 
 int /*<<< orphan*/  venus_helper_init_instance (struct venus_inst*) ; 
 struct venus_core* video_drvdata (struct file*) ; 

__attribute__((used)) static int venc_open(struct file *file)
{
	struct venus_core *core = video_drvdata(file);
	struct venus_inst *inst;
	int ret;

	inst = kzalloc(sizeof(*inst), GFP_KERNEL);
	if (!inst)
		return -ENOMEM;

	INIT_LIST_HEAD(&inst->dpbbufs);
	INIT_LIST_HEAD(&inst->registeredbufs);
	INIT_LIST_HEAD(&inst->internalbufs);
	INIT_LIST_HEAD(&inst->list);
	mutex_init(&inst->lock);

	inst->core = core;
	inst->session_type = VIDC_SESSION_TYPE_ENC;

	venus_helper_init_instance(inst);

	ret = pm_runtime_get_sync(core->dev_enc);
	if (ret < 0)
		goto err_free_inst;

	ret = venc_ctrl_init(inst);
	if (ret)
		goto err_put_sync;

	ret = hfi_session_create(inst, &venc_hfi_ops);
	if (ret)
		goto err_ctrl_deinit;

	venc_inst_init(inst);

	/*
	 * create m2m device for every instance, the m2m context scheduling
	 * is made by firmware side so we do not need to care about.
	 */
	inst->m2m_dev = v4l2_m2m_init(&venc_m2m_ops);
	if (IS_ERR(inst->m2m_dev)) {
		ret = PTR_ERR(inst->m2m_dev);
		goto err_session_destroy;
	}

	inst->m2m_ctx = v4l2_m2m_ctx_init(inst->m2m_dev, inst, m2m_queue_init);
	if (IS_ERR(inst->m2m_ctx)) {
		ret = PTR_ERR(inst->m2m_ctx);
		goto err_m2m_release;
	}

	v4l2_fh_init(&inst->fh, core->vdev_enc);

	inst->fh.ctrl_handler = &inst->ctrl_handler;
	v4l2_fh_add(&inst->fh);
	inst->fh.m2m_ctx = inst->m2m_ctx;
	file->private_data = &inst->fh;

	return 0;

err_m2m_release:
	v4l2_m2m_release(inst->m2m_dev);
err_session_destroy:
	hfi_session_destroy(inst);
err_ctrl_deinit:
	venc_ctrl_deinit(inst);
err_put_sync:
	pm_runtime_put_sync(core->dev_enc);
err_free_inst:
	kfree(inst);
	return ret;
}
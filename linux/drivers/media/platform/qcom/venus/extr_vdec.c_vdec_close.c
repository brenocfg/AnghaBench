#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct venus_inst {TYPE_1__* core; int /*<<< orphan*/  fh; int /*<<< orphan*/  lock; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  m2m_ctx; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi_session_destroy (struct venus_inst*) ; 
 int /*<<< orphan*/  kfree (struct venus_inst*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 struct venus_inst* to_inst (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdec_ctrl_deinit (struct venus_inst*) ; 

__attribute__((used)) static int vdec_close(struct file *file)
{
	struct venus_inst *inst = to_inst(file);

	v4l2_m2m_ctx_release(inst->m2m_ctx);
	v4l2_m2m_release(inst->m2m_dev);
	vdec_ctrl_deinit(inst);
	hfi_session_destroy(inst);
	mutex_destroy(&inst->lock);
	v4l2_fh_del(&inst->fh);
	v4l2_fh_exit(&inst->fh);

	pm_runtime_put_sync(inst->core->dev_dec);

	kfree(inst);
	return 0;
}
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
struct file {struct drm_file* private_data; } ;
struct drm_file {struct amdgpu_fpriv* driver_priv; } ;
struct amdgpu_fpriv {int /*<<< orphan*/  vm; int /*<<< orphan*/  ctx_mgr; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 long MAX_WAIT_SCHED_ENTITY_Q_EMPTY ; 
 long amdgpu_ctx_mgr_entity_flush (int /*<<< orphan*/ *,long) ; 
 long amdgpu_vm_wait_idle (int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static int amdgpu_flush(struct file *f, fl_owner_t id)
{
	struct drm_file *file_priv = f->private_data;
	struct amdgpu_fpriv *fpriv = file_priv->driver_priv;
	long timeout = MAX_WAIT_SCHED_ENTITY_Q_EMPTY;

	timeout = amdgpu_ctx_mgr_entity_flush(&fpriv->ctx_mgr, timeout);
	timeout = amdgpu_vm_wait_idle(&fpriv->vm, timeout);

	return timeout >= 0 ? 0 : timeout;
}
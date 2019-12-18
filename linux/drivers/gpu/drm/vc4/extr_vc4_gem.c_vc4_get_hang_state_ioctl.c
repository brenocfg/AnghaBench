#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct drm_vc4_get_hang_state {size_t bo_count; int /*<<< orphan*/  bo; } ;
struct vc4_hang_state {int /*<<< orphan*/ * bo; struct drm_vc4_get_hang_state user_state; } ;
struct vc4_dev {int /*<<< orphan*/  job_lock; struct vc4_hang_state* hang_state; int /*<<< orphan*/  v3d; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_1__ base; int /*<<< orphan*/  paddr; } ;
struct vc4_bo {TYPE_2__ base; } ;
struct drm_vc4_get_hang_state_bo {size_t handle; int /*<<< orphan*/  size; int /*<<< orphan*/  paddr; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EFAULT ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct drm_vc4_get_hang_state_bo*,int) ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  drm_gem_handle_delete (struct drm_file*,size_t) ; 
 struct drm_vc4_get_hang_state_bo* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_vc4_get_hang_state_bo*) ; 
 int /*<<< orphan*/  memcpy (struct drm_vc4_get_hang_state*,struct drm_vc4_get_hang_state*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_bo* to_vc4_bo (int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_free_hang_state (struct drm_device*,struct vc4_hang_state*) ; 

int
vc4_get_hang_state_ioctl(struct drm_device *dev, void *data,
			 struct drm_file *file_priv)
{
	struct drm_vc4_get_hang_state *get_state = data;
	struct drm_vc4_get_hang_state_bo *bo_state;
	struct vc4_hang_state *kernel_state;
	struct drm_vc4_get_hang_state *state;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	unsigned long irqflags;
	u32 i;
	int ret = 0;

	if (!vc4->v3d) {
		DRM_DEBUG("VC4_GET_HANG_STATE with no VC4 V3D probed\n");
		return -ENODEV;
	}

	spin_lock_irqsave(&vc4->job_lock, irqflags);
	kernel_state = vc4->hang_state;
	if (!kernel_state) {
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		return -ENOENT;
	}
	state = &kernel_state->user_state;

	/* If the user's array isn't big enough, just return the
	 * required array size.
	 */
	if (get_state->bo_count < state->bo_count) {
		get_state->bo_count = state->bo_count;
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		return 0;
	}

	vc4->hang_state = NULL;
	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	/* Save the user's BO pointer, so we don't stomp it with the memcpy. */
	state->bo = get_state->bo;
	memcpy(get_state, state, sizeof(*state));

	bo_state = kcalloc(state->bo_count, sizeof(*bo_state), GFP_KERNEL);
	if (!bo_state) {
		ret = -ENOMEM;
		goto err_free;
	}

	for (i = 0; i < state->bo_count; i++) {
		struct vc4_bo *vc4_bo = to_vc4_bo(kernel_state->bo[i]);
		u32 handle;

		ret = drm_gem_handle_create(file_priv, kernel_state->bo[i],
					    &handle);

		if (ret) {
			state->bo_count = i;
			goto err_delete_handle;
		}
		bo_state[i].handle = handle;
		bo_state[i].paddr = vc4_bo->base.paddr;
		bo_state[i].size = vc4_bo->base.base.size;
	}

	if (copy_to_user(u64_to_user_ptr(get_state->bo),
			 bo_state,
			 state->bo_count * sizeof(*bo_state)))
		ret = -EFAULT;

err_delete_handle:
	if (ret) {
		for (i = 0; i < state->bo_count; i++)
			drm_gem_handle_delete(file_priv, bo_state[i].handle);
	}

err_free:
	vc4_free_hang_state(dev, kernel_state);
	kfree(bo_state);

	return ret;
}
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
typedef  int u64 ;
struct sync_file {int /*<<< orphan*/  file; } ;
struct i915_vma {int* exec_flags; scalar_t__ size; scalar_t__ private; struct i915_vma* batch; int /*<<< orphan*/  fence; int /*<<< orphan*/  obj; } ;
struct TYPE_4__ {int rq; } ;
struct i915_execbuffer {unsigned int* flags; int invalid_flags; int buffer_count; scalar_t__ batch_start_offset; scalar_t__ batch_len; int batch_flags; int /*<<< orphan*/  gem_context; struct drm_i915_gem_exec_object2* exec; struct i915_vma* batch; struct i915_vma* request; TYPE_1__* engine; int /*<<< orphan*/  context; TYPE_2__ reloc_cache; int /*<<< orphan*/  lut_size; struct drm_i915_private* i915; struct i915_vma** vma; struct drm_i915_gem_execbuffer2* args; struct drm_file* file; } ;
struct drm_syncobj {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_execbuffer2 {int flags; int buffer_count; scalar_t__ batch_start_offset; scalar_t__ batch_len; int rsvd2; } ;
struct drm_i915_gem_exec_object2 {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct dma_fence {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bond_execute; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ DBG_FORCE_RELOC ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int EXEC_OBJECT_WRITE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAS_SECURE_BATCHES (struct drm_i915_private*) ; 
 int I915_DISPATCH_PINNED ; 
 int I915_DISPATCH_SECURE ; 
 int I915_EXEC_FENCE_IN ; 
 int I915_EXEC_FENCE_OUT ; 
 int I915_EXEC_FENCE_SUBMIT ; 
 int I915_EXEC_IS_PINNED ; 
 int I915_EXEC_NO_RELOC ; 
 int I915_EXEC_SECURE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int PTR_ERR (struct i915_vma*) ; 
 int __EXEC_HAS_RELOC ; 
 int __EXEC_INTERNAL_FLAGS ; 
 int __EXEC_OBJECT_INTERNAL_FLAGS ; 
 int __EXEC_OBJECT_UNKNOWN_FLAGS ; 
 int __I915_EXEC_ILLEGAL_FLAGS ; 
 int /*<<< orphan*/  add_to_client (struct i915_vma*,struct drm_file*) ; 
 int await_fence_array (struct i915_execbuffer*,struct drm_syncobj**) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  drm_is_current_master (struct drm_file*) ; 
 int eb_create (struct i915_execbuffer*) ; 
 int /*<<< orphan*/  eb_destroy (struct i915_execbuffer*) ; 
 struct i915_vma* eb_parse (struct i915_execbuffer*) ; 
 int eb_pin_engine (struct i915_execbuffer*,struct drm_file*,struct drm_i915_gem_execbuffer2*) ; 
 int /*<<< orphan*/  eb_release_vmas (struct i915_execbuffer*) ; 
 int eb_relocate (struct i915_execbuffer*) ; 
 int eb_select_context (struct i915_execbuffer*) ; 
 int eb_submit (struct i915_execbuffer*) ; 
 int /*<<< orphan*/  eb_unpin_engine (struct i915_execbuffer*) ; 
 scalar_t__ eb_use_cmdparser (struct i915_execbuffer*) ; 
 int /*<<< orphan*/  fd_install (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_put (int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_gem_object_ggtt_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_vma*) ; 
 int i915_request_await_dma_fence (struct i915_vma*,struct dma_fence*) ; 
 int i915_request_await_execution (struct i915_vma*,struct dma_fence*,int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_request_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_engine_pool_mark_active (scalar_t__,struct i915_vma*) ; 
 int /*<<< orphan*/  intel_engine_pool_put (scalar_t__) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int /*<<< orphan*/  reloc_cache_init (TYPE_2__*,struct drm_i915_private*) ; 
 int /*<<< orphan*/  signal_fence_array (struct i915_execbuffer*,struct drm_syncobj**) ; 
 struct sync_file* sync_file_create (int /*<<< orphan*/ *) ; 
 struct dma_fence* sync_file_get_fence (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int /*<<< orphan*/  trace_i915_request_queue (struct i915_vma*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
i915_gem_do_execbuffer(struct drm_device *dev,
		       struct drm_file *file,
		       struct drm_i915_gem_execbuffer2 *args,
		       struct drm_i915_gem_exec_object2 *exec,
		       struct drm_syncobj **fences)
{
	struct drm_i915_private *i915 = to_i915(dev);
	struct i915_execbuffer eb;
	struct dma_fence *in_fence = NULL;
	struct dma_fence *exec_fence = NULL;
	struct sync_file *out_fence = NULL;
	int out_fence_fd = -1;
	int err;

	BUILD_BUG_ON(__EXEC_INTERNAL_FLAGS & ~__I915_EXEC_ILLEGAL_FLAGS);
	BUILD_BUG_ON(__EXEC_OBJECT_INTERNAL_FLAGS &
		     ~__EXEC_OBJECT_UNKNOWN_FLAGS);

	eb.i915 = i915;
	eb.file = file;
	eb.args = args;
	if (DBG_FORCE_RELOC || !(args->flags & I915_EXEC_NO_RELOC))
		args->flags |= __EXEC_HAS_RELOC;

	eb.exec = exec;
	eb.vma = (struct i915_vma **)(exec + args->buffer_count + 1);
	eb.vma[0] = NULL;
	eb.flags = (unsigned int *)(eb.vma + args->buffer_count + 1);

	eb.invalid_flags = __EXEC_OBJECT_UNKNOWN_FLAGS;
	reloc_cache_init(&eb.reloc_cache, eb.i915);

	eb.buffer_count = args->buffer_count;
	eb.batch_start_offset = args->batch_start_offset;
	eb.batch_len = args->batch_len;

	eb.batch_flags = 0;
	if (args->flags & I915_EXEC_SECURE) {
		if (INTEL_GEN(i915) >= 11)
			return -ENODEV;

		/* Return -EPERM to trigger fallback code on old binaries. */
		if (!HAS_SECURE_BATCHES(i915))
			return -EPERM;

		if (!drm_is_current_master(file) || !capable(CAP_SYS_ADMIN))
			return -EPERM;

		eb.batch_flags |= I915_DISPATCH_SECURE;
	}
	if (args->flags & I915_EXEC_IS_PINNED)
		eb.batch_flags |= I915_DISPATCH_PINNED;

	if (args->flags & I915_EXEC_FENCE_IN) {
		in_fence = sync_file_get_fence(lower_32_bits(args->rsvd2));
		if (!in_fence)
			return -EINVAL;
	}

	if (args->flags & I915_EXEC_FENCE_SUBMIT) {
		if (in_fence) {
			err = -EINVAL;
			goto err_in_fence;
		}

		exec_fence = sync_file_get_fence(lower_32_bits(args->rsvd2));
		if (!exec_fence) {
			err = -EINVAL;
			goto err_in_fence;
		}
	}

	if (args->flags & I915_EXEC_FENCE_OUT) {
		out_fence_fd = get_unused_fd_flags(O_CLOEXEC);
		if (out_fence_fd < 0) {
			err = out_fence_fd;
			goto err_exec_fence;
		}
	}

	err = eb_create(&eb);
	if (err)
		goto err_out_fence;

	GEM_BUG_ON(!eb.lut_size);

	err = eb_select_context(&eb);
	if (unlikely(err))
		goto err_destroy;

	err = eb_pin_engine(&eb, file, args);
	if (unlikely(err))
		goto err_context;

	err = i915_mutex_lock_interruptible(dev);
	if (err)
		goto err_engine;

	err = eb_relocate(&eb);
	if (err) {
		/*
		 * If the user expects the execobject.offset and
		 * reloc.presumed_offset to be an exact match,
		 * as for using NO_RELOC, then we cannot update
		 * the execobject.offset until we have completed
		 * relocation.
		 */
		args->flags &= ~__EXEC_HAS_RELOC;
		goto err_vma;
	}

	if (unlikely(*eb.batch->exec_flags & EXEC_OBJECT_WRITE)) {
		DRM_DEBUG("Attempting to use self-modifying batch buffer\n");
		err = -EINVAL;
		goto err_vma;
	}
	if (eb.batch_start_offset > eb.batch->size ||
	    eb.batch_len > eb.batch->size - eb.batch_start_offset) {
		DRM_DEBUG("Attempting to use out-of-bounds batch\n");
		err = -EINVAL;
		goto err_vma;
	}

	if (eb.batch_len == 0)
		eb.batch_len = eb.batch->size - eb.batch_start_offset;

	if (eb_use_cmdparser(&eb)) {
		struct i915_vma *vma;

		vma = eb_parse(&eb);
		if (IS_ERR(vma)) {
			err = PTR_ERR(vma);
			goto err_vma;
		}
	}

	/*
	 * snb/ivb/vlv conflate the "batch in ppgtt" bit with the "non-secure
	 * batch" bit. Hence we need to pin secure batches into the global gtt.
	 * hsw should have this fixed, but bdw mucks it up again. */
	if (eb.batch_flags & I915_DISPATCH_SECURE) {
		struct i915_vma *vma;

		/*
		 * So on first glance it looks freaky that we pin the batch here
		 * outside of the reservation loop. But:
		 * - The batch is already pinned into the relevant ppgtt, so we
		 *   already have the backing storage fully allocated.
		 * - No other BO uses the global gtt (well contexts, but meh),
		 *   so we don't really have issues with multiple objects not
		 *   fitting due to fragmentation.
		 * So this is actually safe.
		 */
		vma = i915_gem_object_ggtt_pin(eb.batch->obj, NULL, 0, 0, 0);
		if (IS_ERR(vma)) {
			err = PTR_ERR(vma);
			goto err_vma;
		}

		eb.batch = vma;
	}

	/* All GPU relocation batches must be submitted prior to the user rq */
	GEM_BUG_ON(eb.reloc_cache.rq);

	/* Allocate a request for this batch buffer nice and early. */
	eb.request = i915_request_create(eb.context);
	if (IS_ERR(eb.request)) {
		err = PTR_ERR(eb.request);
		goto err_batch_unpin;
	}

	if (in_fence) {
		err = i915_request_await_dma_fence(eb.request, in_fence);
		if (err < 0)
			goto err_request;
	}

	if (exec_fence) {
		err = i915_request_await_execution(eb.request, exec_fence,
						   eb.engine->bond_execute);
		if (err < 0)
			goto err_request;
	}

	if (fences) {
		err = await_fence_array(&eb, fences);
		if (err)
			goto err_request;
	}

	if (out_fence_fd != -1) {
		out_fence = sync_file_create(&eb.request->fence);
		if (!out_fence) {
			err = -ENOMEM;
			goto err_request;
		}
	}

	/*
	 * Whilst this request exists, batch_obj will be on the
	 * active_list, and so will hold the active reference. Only when this
	 * request is retired will the the batch_obj be moved onto the
	 * inactive_list and lose its active reference. Hence we do not need
	 * to explicitly hold another reference here.
	 */
	eb.request->batch = eb.batch;
	if (eb.batch->private)
		intel_engine_pool_mark_active(eb.batch->private, eb.request);

	trace_i915_request_queue(eb.request, eb.batch_flags);
	err = eb_submit(&eb);
err_request:
	add_to_client(eb.request, file);
	i915_request_add(eb.request);

	if (fences)
		signal_fence_array(&eb, fences);

	if (out_fence) {
		if (err == 0) {
			fd_install(out_fence_fd, out_fence->file);
			args->rsvd2 &= GENMASK_ULL(31, 0); /* keep in-fence */
			args->rsvd2 |= (u64)out_fence_fd << 32;
			out_fence_fd = -1;
		} else {
			fput(out_fence->file);
		}
	}

err_batch_unpin:
	if (eb.batch_flags & I915_DISPATCH_SECURE)
		i915_vma_unpin(eb.batch);
	if (eb.batch->private)
		intel_engine_pool_put(eb.batch->private);
err_vma:
	if (eb.exec)
		eb_release_vmas(&eb);
	mutex_unlock(&dev->struct_mutex);
err_engine:
	eb_unpin_engine(&eb);
err_context:
	i915_gem_context_put(eb.gem_context);
err_destroy:
	eb_destroy(&eb);
err_out_fence:
	if (out_fence_fd != -1)
		put_unused_fd(out_fence_fd);
err_exec_fence:
	dma_fence_put(exec_fence);
err_in_fence:
	dma_fence_put(in_fence);
	return err;
}
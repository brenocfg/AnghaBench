#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_sseu {int slice_mask; int subslice_mask; } ;
struct intel_engine_cs {struct intel_sseu sseu; } ;
struct intel_context {int dummy; } ;
typedef  struct intel_context i915_gem_context ;
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; TYPE_2__ drm; struct intel_engine_cs** engine; } ;
typedef  struct intel_context drm_i915_gem_object ;
typedef  struct intel_context drm_file ;
struct TYPE_4__ {int /*<<< orphan*/  has_slice_pg; } ;
struct TYPE_6__ {TYPE_1__ sseu; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I915_WAIT_LOCKED ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct intel_context*) ; 
 size_t RCS0 ; 
 TYPE_3__* RUNTIME_INFO (struct drm_i915_private*) ; 
 unsigned int TEST_RESET ; 
 int __sseu_test (char const*,unsigned int,struct intel_context*,struct intel_context*,struct intel_sseu) ; 
 int hweight32 (int) ; 
 int /*<<< orphan*/  i915_gem_context_clear_bannable (struct intel_context*) ; 
 struct intel_context* i915_gem_context_get_engine (struct intel_context*,size_t) ; 
 struct intel_context* i915_gem_object_create_internal (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct intel_context*) ; 
 scalar_t__ igt_flush_test (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igt_global_reset_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igt_global_reset_unlock (int /*<<< orphan*/ *) ; 
 int intel_context_pin (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_put (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_unpin (struct intel_context*) ; 
 struct intel_context* live_context (struct drm_i915_private*,struct intel_context*) ; 
 struct intel_context* mock_file (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mock_file_free (struct drm_i915_private*,struct intel_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,unsigned int,int,int) ; 

__attribute__((used)) static int
__igt_ctx_sseu(struct drm_i915_private *i915,
	       const char *name,
	       unsigned int flags)
{
	struct intel_engine_cs *engine = i915->engine[RCS0];
	struct drm_i915_gem_object *obj;
	struct i915_gem_context *ctx;
	struct intel_context *ce;
	struct intel_sseu pg_sseu;
	struct drm_file *file;
	int ret;

	if (INTEL_GEN(i915) < 9 || !engine)
		return 0;

	if (!RUNTIME_INFO(i915)->sseu.has_slice_pg)
		return 0;

	if (hweight32(engine->sseu.slice_mask) < 2)
		return 0;

	/*
	 * Gen11 VME friendly power-gated configuration with half enabled
	 * sub-slices.
	 */
	pg_sseu = engine->sseu;
	pg_sseu.slice_mask = 1;
	pg_sseu.subslice_mask =
		~(~0 << (hweight32(engine->sseu.subslice_mask) / 2));

	pr_info("SSEU subtest '%s', flags=%x, def_slices=%u, pg_slices=%u\n",
		name, flags, hweight32(engine->sseu.slice_mask),
		hweight32(pg_sseu.slice_mask));

	file = mock_file(i915);
	if (IS_ERR(file))
		return PTR_ERR(file);

	if (flags & TEST_RESET)
		igt_global_reset_lock(&i915->gt);

	mutex_lock(&i915->drm.struct_mutex);

	ctx = live_context(i915, file);
	if (IS_ERR(ctx)) {
		ret = PTR_ERR(ctx);
		goto out_unlock;
	}
	i915_gem_context_clear_bannable(ctx); /* to reset and beyond! */

	obj = i915_gem_object_create_internal(i915, PAGE_SIZE);
	if (IS_ERR(obj)) {
		ret = PTR_ERR(obj);
		goto out_unlock;
	}

	ce = i915_gem_context_get_engine(ctx, RCS0);
	if (IS_ERR(ce)) {
		ret = PTR_ERR(ce);
		goto out_put;
	}

	ret = intel_context_pin(ce);
	if (ret)
		goto out_context;

	/* First set the default mask. */
	ret = __sseu_test(name, flags, ce, obj, engine->sseu);
	if (ret)
		goto out_fail;

	/* Then set a power-gated configuration. */
	ret = __sseu_test(name, flags, ce, obj, pg_sseu);
	if (ret)
		goto out_fail;

	/* Back to defaults. */
	ret = __sseu_test(name, flags, ce, obj, engine->sseu);
	if (ret)
		goto out_fail;

	/* One last power-gated configuration for the road. */
	ret = __sseu_test(name, flags, ce, obj, pg_sseu);
	if (ret)
		goto out_fail;

out_fail:
	if (igt_flush_test(i915, I915_WAIT_LOCKED))
		ret = -EIO;

	intel_context_unpin(ce);
out_context:
	intel_context_put(ce);
out_put:
	i915_gem_object_put(obj);

out_unlock:
	mutex_unlock(&i915->drm.struct_mutex);

	if (flags & TEST_RESET)
		igt_global_reset_unlock(&i915->gt);

	mock_file_free(i915, file);

	if (ret)
		pr_err("%s: Failed with %d!\n", name, ret);

	return ret;
}
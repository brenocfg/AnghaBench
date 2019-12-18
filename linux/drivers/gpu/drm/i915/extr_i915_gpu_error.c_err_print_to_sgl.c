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
struct i915_gpu_state {int /*<<< orphan*/  sgl; int /*<<< orphan*/  i915; } ;
struct drm_i915_error_state_buf {scalar_t__ cur; scalar_t__ end; int err; scalar_t__ sgl; int /*<<< orphan*/ * buf; scalar_t__ bytes; int /*<<< orphan*/  iter; int /*<<< orphan*/  i915; } ;
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct i915_gpu_state*) ; 
 int PTR_ERR (struct i915_gpu_state*) ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __err_print_to_sgl (struct drm_i915_error_state_buf*,struct i915_gpu_state*) ; 
 int /*<<< orphan*/  __sg_set_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  err_free_sgl (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct drm_i915_error_state_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_mark_end (scalar_t__) ; 

__attribute__((used)) static int err_print_to_sgl(struct i915_gpu_state *error)
{
	struct drm_i915_error_state_buf m;

	if (IS_ERR(error))
		return PTR_ERR(error);

	if (READ_ONCE(error->sgl))
		return 0;

	memset(&m, 0, sizeof(m));
	m.i915 = error->i915;

	__err_print_to_sgl(&m, error);

	if (m.buf) {
		__sg_set_buf(m.cur++, m.buf, m.bytes, m.iter);
		m.bytes = 0;
		m.buf = NULL;
	}
	if (m.cur) {
		GEM_BUG_ON(m.end < m.cur);
		sg_mark_end(m.cur - 1);
	}
	GEM_BUG_ON(m.sgl && !m.cur);

	if (m.err) {
		err_free_sgl(m.sgl);
		return m.err;
	}

	if (cmpxchg(&error->sgl, NULL, m.sgl))
		err_free_sgl(m.sgl);

	return 0;
}
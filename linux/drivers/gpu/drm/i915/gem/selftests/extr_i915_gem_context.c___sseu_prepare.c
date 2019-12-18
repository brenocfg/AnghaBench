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
struct intel_context {TYPE_1__* engine; } ;
struct igt_spinner {int dummy; } ;
struct i915_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct i915_request*) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (struct i915_request*) ; 
 unsigned int TEST_BUSY ; 
 unsigned int TEST_RESET ; 
 int /*<<< orphan*/  fetch_and_zero (struct igt_spinner**) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 struct i915_request* igt_spinner_create_request (struct igt_spinner*,struct intel_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igt_spinner_end (struct igt_spinner*) ; 
 int /*<<< orphan*/  igt_spinner_fini (struct igt_spinner*) ; 
 int igt_spinner_init (struct igt_spinner*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igt_wait_for_spinner (struct igt_spinner*,struct i915_request*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct igt_spinner* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int
__sseu_prepare(const char *name,
	       unsigned int flags,
	       struct intel_context *ce,
	       struct igt_spinner **spin)
{
	struct i915_request *rq;
	int ret;

	*spin = NULL;
	if (!(flags & (TEST_BUSY | TEST_RESET)))
		return 0;

	*spin = kzalloc(sizeof(**spin), GFP_KERNEL);
	if (!*spin)
		return -ENOMEM;

	ret = igt_spinner_init(*spin, ce->engine->gt);
	if (ret)
		goto err_free;

	rq = igt_spinner_create_request(*spin, ce, MI_NOOP);
	if (IS_ERR(rq)) {
		ret = PTR_ERR(rq);
		goto err_fini;
	}

	i915_request_add(rq);

	if (!igt_wait_for_spinner(*spin, rq)) {
		pr_err("%s: Spinner failed to start!\n", name);
		ret = -ETIMEDOUT;
		goto err_end;
	}

	return 0;

err_end:
	igt_spinner_end(*spin);
err_fini:
	igt_spinner_fini(*spin);
err_free:
	kfree(fetch_and_zero(spin));
	return ret;
}
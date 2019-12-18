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
struct tasklet_struct {int dummy; } ;
struct TYPE_2__ {struct tasklet_struct tasklet; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; TYPE_1__ execlists; } ;
struct igt_atomic_section {int /*<<< orphan*/  name; int /*<<< orphan*/  (* critical_section_end ) () ;int /*<<< orphan*/  (* critical_section_begin ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int intel_engine_reset (struct intel_engine_cs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  tasklet_disable_nosync (struct tasklet_struct* const) ; 
 int /*<<< orphan*/  tasklet_enable (struct tasklet_struct* const) ; 

__attribute__((used)) static int __igt_atomic_reset_engine(struct intel_engine_cs *engine,
				     const struct igt_atomic_section *p,
				     const char *mode)
{
	struct tasklet_struct * const t = &engine->execlists.tasklet;
	int err;

	GEM_TRACE("i915_reset_engine(%s:%s) under %s\n",
		  engine->name, mode, p->name);

	tasklet_disable_nosync(t);
	p->critical_section_begin();

	err = intel_engine_reset(engine, NULL);

	p->critical_section_end();
	tasklet_enable(t);

	if (err)
		pr_err("i915_reset_engine(%s:%s) failed under %s\n",
		       engine->name, mode, p->name);

	return err;
}
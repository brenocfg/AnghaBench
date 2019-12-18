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
typedef  scalar_t__ u32 ;
struct intel_guc_log {int /*<<< orphan*/  level; struct i915_vma* vma; } ;
struct intel_guc {int dummy; } ;
struct i915_vma {int dummy; } ;

/* Variables and functions */
 scalar_t__ CRASH_BUFFER_SIZE ; 
 scalar_t__ DPC_BUFFER_SIZE ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (struct i915_vma*) ; 
 int /*<<< orphan*/  GUC_LOG_LEVEL_IS_VERBOSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUC_LOG_LEVEL_TO_VERBOSITY (int /*<<< orphan*/ ) ; 
 scalar_t__ ISR_BUFFER_SIZE ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 scalar_t__ PAGE_SIZE ; 
 int PTR_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  __get_default_log_level (struct intel_guc_log*) ; 
 int /*<<< orphan*/  enableddisabled (int /*<<< orphan*/ ) ; 
 struct i915_vma* intel_guc_allocate_vma (struct intel_guc*,scalar_t__) ; 
 struct intel_guc* log_to_guc (struct intel_guc_log*) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

int intel_guc_log_create(struct intel_guc_log *log)
{
	struct intel_guc *guc = log_to_guc(log);
	struct i915_vma *vma;
	u32 guc_log_size;
	int ret;

	GEM_BUG_ON(log->vma);

	/*
	 *  GuC Log buffer Layout
	 *
	 *  +===============================+ 00B
	 *  |    Crash dump state header    |
	 *  +-------------------------------+ 32B
	 *  |       DPC state header        |
	 *  +-------------------------------+ 64B
	 *  |       ISR state header        |
	 *  +-------------------------------+ 96B
	 *  |                               |
	 *  +===============================+ PAGE_SIZE (4KB)
	 *  |        Crash Dump logs        |
	 *  +===============================+ + CRASH_SIZE
	 *  |           DPC logs            |
	 *  +===============================+ + DPC_SIZE
	 *  |           ISR logs            |
	 *  +===============================+ + ISR_SIZE
	 */
	guc_log_size = PAGE_SIZE + CRASH_BUFFER_SIZE + DPC_BUFFER_SIZE +
			ISR_BUFFER_SIZE;

	vma = intel_guc_allocate_vma(guc, guc_log_size);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto err;
	}

	log->vma = vma;

	log->level = __get_default_log_level(log);
	DRM_DEBUG_DRIVER("guc_log_level=%d (%s, verbose:%s, verbosity:%d)\n",
			 log->level, enableddisabled(log->level),
			 yesno(GUC_LOG_LEVEL_IS_VERBOSE(log->level)),
			 GUC_LOG_LEVEL_TO_VERBOSITY(log->level));

	return 0;

err:
	DRM_ERROR("Failed to allocate GuC log buffer. %d\n", ret);
	return ret;
}
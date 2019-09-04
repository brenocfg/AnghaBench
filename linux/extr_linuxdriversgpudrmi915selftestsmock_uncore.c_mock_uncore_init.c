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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_READ_MMIO_VFUNCS (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSIGN_WRITE_MMIO_VFUNCS (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nop ; 

void mock_uncore_init(struct drm_i915_private *i915)
{
	ASSIGN_WRITE_MMIO_VFUNCS(i915, nop);
	ASSIGN_READ_MMIO_VFUNCS(i915, nop);
}
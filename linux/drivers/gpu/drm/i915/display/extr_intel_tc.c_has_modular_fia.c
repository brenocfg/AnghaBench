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
struct drm_i915_private {int /*<<< orphan*/  uncore; } ;
struct TYPE_3__ {int /*<<< orphan*/  has_modular_fia; } ;
struct TYPE_4__ {TYPE_1__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIA1 ; 
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 
 int MODULAR_FIA_MASK ; 
 int /*<<< orphan*/  PORT_TX_DFLEXDPSP (int /*<<< orphan*/ ) ; 
 int intel_uncore_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool has_modular_fia(struct drm_i915_private *i915)
{
	if (!INTEL_INFO(i915)->display.has_modular_fia)
		return false;

	return intel_uncore_read(&i915->uncore,
				 PORT_TX_DFLEXDPSP(FIA1)) & MODULAR_FIA_MASK;
}
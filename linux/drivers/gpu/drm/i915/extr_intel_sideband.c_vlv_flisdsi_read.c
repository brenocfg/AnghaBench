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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPIO_DEVFN ; 
 int /*<<< orphan*/  IOSF_PORT_FLISDSI ; 
 int /*<<< orphan*/  SB_CRRDDA_NP ; 
 int /*<<< orphan*/  vlv_sideband_rw (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u32 vlv_flisdsi_read(struct drm_i915_private *i915, u32 reg)
{
	u32 val = 0;

	vlv_sideband_rw(i915, DPIO_DEVFN, IOSF_PORT_FLISDSI, SB_CRRDDA_NP,
			reg, &val);
	return val;
}
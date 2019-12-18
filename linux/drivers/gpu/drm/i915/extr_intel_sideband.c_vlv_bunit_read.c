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
 int /*<<< orphan*/  IOSF_PORT_BUNIT ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_CRRDDA_NP ; 
 int /*<<< orphan*/  vlv_sideband_rw (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u32 vlv_bunit_read(struct drm_i915_private *i915, u32 reg)
{
	u32 val = 0;

	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), IOSF_PORT_BUNIT,
			SB_CRRDDA_NP, reg, &val);

	return val;
}
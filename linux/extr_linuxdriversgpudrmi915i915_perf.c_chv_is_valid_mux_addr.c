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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ gen7_is_valid_mux_addr (struct drm_i915_private*,int) ; 

__attribute__((used)) static bool chv_is_valid_mux_addr(struct drm_i915_private *dev_priv, u32 addr)
{
	return gen7_is_valid_mux_addr(dev_priv, addr) ||
		(addr >= 0x182300 && addr <= 0x1823A4);
}
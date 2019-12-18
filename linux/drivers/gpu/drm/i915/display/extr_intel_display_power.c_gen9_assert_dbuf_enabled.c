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
 int /*<<< orphan*/  DBUF_CTL ; 
 int DBUF_POWER_REQUEST ; 
 int DBUF_POWER_STATE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 

__attribute__((used)) static void gen9_assert_dbuf_enabled(struct drm_i915_private *dev_priv)
{
	u32 tmp = I915_READ(DBUF_CTL);

	WARN((tmp & (DBUF_POWER_STATE | DBUF_POWER_REQUEST)) !=
	     (DBUF_POWER_STATE | DBUF_POWER_REQUEST),
	     "Unexpected DBuf power power state (0x%08x)\n", tmp);
}
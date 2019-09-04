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
 int /*<<< orphan*/  CSR_HTP_SKL ; 
 int /*<<< orphan*/  CSR_PROGRAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_SSP_BASE ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 

__attribute__((used)) static void assert_csr_loaded(struct drm_i915_private *dev_priv)
{
	WARN_ONCE(!I915_READ(CSR_PROGRAM(0)),
		  "CSR program storage start is NULL\n");
	WARN_ONCE(!I915_READ(CSR_SSP_BASE), "CSR SSP Base Not fine\n");
	WARN_ONCE(!I915_READ(CSR_HTP_SKL), "CSR HTP Not fine\n");
}
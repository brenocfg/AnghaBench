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
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DVOA ; 
 int /*<<< orphan*/  DVOB ; 
 int PORT_A ; 
 int PORT_B ; 
 int PORT_C ; 
 scalar_t__ i915_mmio_reg_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum port intel_dvo_port(i915_reg_t dvo_reg)
{
	if (i915_mmio_reg_equal(dvo_reg, DVOA))
		return PORT_A;
	else if (i915_mmio_reg_equal(dvo_reg, DVOB))
		return PORT_B;
	else
		return PORT_C;
}
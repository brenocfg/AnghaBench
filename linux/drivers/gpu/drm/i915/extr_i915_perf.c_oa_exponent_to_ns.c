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
typedef  int /*<<< orphan*/  u64 ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {unsigned long long cs_timestamp_frequency_khz; } ;

/* Variables and functions */
 TYPE_1__* RUNTIME_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  div64_u64 (unsigned long long,unsigned long long) ; 

__attribute__((used)) static u64 oa_exponent_to_ns(struct drm_i915_private *dev_priv, int exponent)
{
	return div64_u64(1000000000ULL * (2ULL << exponent),
			 1000ULL * RUNTIME_INFO(dev_priv)->cs_timestamp_frequency_khz);
}
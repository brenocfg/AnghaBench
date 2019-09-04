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

/* Variables and functions */
 scalar_t__ DRM_I915_HANGCHECK_JIFFIES ; 
 scalar_t__ jiffies ; 
 unsigned long round_jiffies_up (scalar_t__) ; 

__attribute__((used)) static unsigned long wait_timeout(void)
{
	return round_jiffies_up(jiffies + DRM_I915_HANGCHECK_JIFFIES);
}
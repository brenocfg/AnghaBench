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
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int I915_MAX_PIPES ; 
 scalar_t__ pipe_is_enabled (struct intel_vgpu*,int) ; 

__attribute__((used)) static int get_active_pipe(struct intel_vgpu *vgpu)
{
	int i;

	for (i = 0; i < I915_MAX_PIPES; i++)
		if (pipe_is_enabled(vgpu, i))
			break;

	return i;
}
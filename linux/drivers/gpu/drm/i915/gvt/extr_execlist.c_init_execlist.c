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
typedef  int /*<<< orphan*/  intel_engine_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  reset_execlist (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_execlist(struct intel_vgpu *vgpu,
			 intel_engine_mask_t engine_mask)
{
	reset_execlist(vgpu, engine_mask);
	return 0;
}
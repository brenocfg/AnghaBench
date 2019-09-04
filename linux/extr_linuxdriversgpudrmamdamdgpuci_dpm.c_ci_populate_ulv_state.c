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
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  SMU7_Discrete_Ulv ;

/* Variables and functions */
 int ci_populate_ulv_level (struct amdgpu_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ci_populate_ulv_state(struct amdgpu_device *adev,
				 SMU7_Discrete_Ulv *ulv_level)
{
	return ci_populate_ulv_level(adev, ulv_level);
}
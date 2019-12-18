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
struct kfd2kgd_calls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfd2kgd ; 

struct kfd2kgd_calls *amdgpu_amdkfd_gfx_8_0_get_functions(void)
{
	return (struct kfd2kgd_calls *)&kfd2kgd;
}
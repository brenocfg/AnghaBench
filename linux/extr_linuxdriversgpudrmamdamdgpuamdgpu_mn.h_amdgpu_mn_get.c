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
struct amdgpu_mn {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_mn_type { ____Placeholder_amdgpu_mn_type } amdgpu_mn_type ;

/* Variables and functions */

__attribute__((used)) static inline struct amdgpu_mn *amdgpu_mn_get(struct amdgpu_device *adev,
					      enum amdgpu_mn_type type)
{
	return NULL;
}
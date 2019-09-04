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
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static inline int amdgpu_mn_register(struct amdgpu_bo *bo, unsigned long addr)
{
	return -ENODEV;
}
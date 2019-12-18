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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GMC_HOLE_END ; 
 int /*<<< orphan*/  AMDGPU_GMC_HOLE_START ; 

__attribute__((used)) static inline uint64_t amdgpu_gmc_sign_extend(uint64_t addr)
{
	if (addr >= AMDGPU_GMC_HOLE_START)
		addr |= AMDGPU_GMC_HOLE_END;

	return addr;
}
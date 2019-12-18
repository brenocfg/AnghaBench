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
struct amdgpu_ih_ring {int /*<<< orphan*/  rptr; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmIH_RB_RPTR ; 

__attribute__((used)) static void cik_ih_set_rptr(struct amdgpu_device *adev,
			    struct amdgpu_ih_ring *ih)
{
	WREG32(mmIH_RB_RPTR, ih->rptr);
}
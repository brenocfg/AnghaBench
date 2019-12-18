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
typedef  int u32 ;
struct amdgpu_ih_ring {int rptr; int ptr_mask; int /*<<< orphan*/ * wptr_cpu; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IH_RB_CNTL__WPTR_OVERFLOW_CLEAR_MASK ; 
 int IH_RB_WPTR__RB_OVERFLOW_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmIH_RB_CNTL ; 

__attribute__((used)) static u32 cik_ih_get_wptr(struct amdgpu_device *adev,
			   struct amdgpu_ih_ring *ih)
{
	u32 wptr, tmp;

	wptr = le32_to_cpu(*ih->wptr_cpu);

	if (wptr & IH_RB_WPTR__RB_OVERFLOW_MASK) {
		wptr &= ~IH_RB_WPTR__RB_OVERFLOW_MASK;
		/* When a ring buffer overflow happen start parsing interrupt
		 * from the last not overwritten vector (wptr + 16). Hopefully
		 * this should allow us to catchup.
		 */
		dev_warn(adev->dev, "IH ring buffer overflow (0x%08X, 0x%08X, 0x%08X)\n",
			 wptr, ih->rptr, (wptr + 16) & ih->ptr_mask);
		ih->rptr = (wptr + 16) & ih->ptr_mask;
		tmp = RREG32(mmIH_RB_CNTL);
		tmp |= IH_RB_CNTL__WPTR_OVERFLOW_CLEAR_MASK;
		WREG32(mmIH_RB_CNTL, tmp);
	}
	return (wptr & ih->ptr_mask);
}
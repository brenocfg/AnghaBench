#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct csio_hw {int pfn; TYPE_1__* pdev; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int CSIO_HW_CHIP_MASK ; 
 int CSIO_MAX_PFN ; 
 int EIO ; 
 int /*<<< orphan*/  PL_WHOAMI_A ; 
 int SOURCEPF_G (int) ; 
 int T6_SOURCEPF_G (int) ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,int,int) ; 
 scalar_t__ csio_is_t5 (int) ; 
 int csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int
csio_hw_dev_ready(struct csio_hw *hw)
{
	uint32_t reg;
	int cnt = 6;
	int src_pf;

	while (((reg = csio_rd_reg32(hw, PL_WHOAMI_A)) == 0xFFFFFFFF) &&
	       (--cnt != 0))
		mdelay(100);

	if (csio_is_t5(hw->pdev->device & CSIO_HW_CHIP_MASK))
		src_pf = SOURCEPF_G(reg);
	else
		src_pf = T6_SOURCEPF_G(reg);

	if ((cnt == 0) && (((int32_t)(src_pf) < 0) ||
			   (src_pf >= CSIO_MAX_PFN))) {
		csio_err(hw, "PL_WHOAMI returned 0x%x, cnt:%d\n", reg, cnt);
		return -EIO;
	}

	hw->pfn = src_pf;

	return 0;
}
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

/* Variables and functions */
 int PWRDWN_SEQ_POWERDOWN_PLL ; 
 int /*<<< orphan*/  SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK ; 
 int SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT ; 
 int /*<<< orphan*/  ddr_ctrl_set (int) ; 
 int /*<<< orphan*/  shimphy_set (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void s3entry_method1(void)
{
	/*
	 * S3 Entry Sequence
	 * -----------------
	 * Step 1: SHIMPHY_ADDR_CNTL_0_DDR_PAD_CNTRL [ S3_PWRDWN_SEQ ] = 3
	 * Step 2: MEMC_DDR_0_WARM_BOOT [ WARM_BOOT ] = 1
	 */
	shimphy_set((PWRDWN_SEQ_POWERDOWN_PLL <<
		    SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT),
		    ~SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK);

	ddr_ctrl_set(true);
}
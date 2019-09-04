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
struct ipu_csi {int /*<<< orphan*/  lock; int /*<<< orphan*/  clk_ipu; } ;

/* Variables and functions */
 int CSI_TEST_GEN_B_MASK ; 
 int CSI_TEST_GEN_B_SHIFT ; 
 int CSI_TEST_GEN_G_MASK ; 
 int CSI_TEST_GEN_G_SHIFT ; 
 int CSI_TEST_GEN_MODE_EN ; 
 int CSI_TEST_GEN_R_MASK ; 
 int CSI_TEST_GEN_R_SHIFT ; 
 int /*<<< orphan*/  CSI_TST_CTRL ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int ipu_csi_read (struct ipu_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_set_testgen_mclk (struct ipu_csi*,int,int) ; 
 int /*<<< orphan*/  ipu_csi_write (struct ipu_csi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_csi_set_test_generator(struct ipu_csi *csi, bool active,
				u32 r_value, u32 g_value, u32 b_value,
				u32 pix_clk)
{
	unsigned long flags;
	u32 ipu_clk = clk_get_rate(csi->clk_ipu);
	u32 temp;

	spin_lock_irqsave(&csi->lock, flags);

	temp = ipu_csi_read(csi, CSI_TST_CTRL);

	if (!active) {
		temp &= ~CSI_TEST_GEN_MODE_EN;
		ipu_csi_write(csi, temp, CSI_TST_CTRL);
	} else {
		/* Set sensb_mclk div_ratio */
		ipu_csi_set_testgen_mclk(csi, pix_clk, ipu_clk);

		temp &= ~(CSI_TEST_GEN_R_MASK | CSI_TEST_GEN_G_MASK |
			  CSI_TEST_GEN_B_MASK);
		temp |= CSI_TEST_GEN_MODE_EN;
		temp |= (r_value << CSI_TEST_GEN_R_SHIFT) |
			(g_value << CSI_TEST_GEN_G_SHIFT) |
			(b_value << CSI_TEST_GEN_B_SHIFT);
		ipu_csi_write(csi, temp, CSI_TST_CTRL);
	}

	spin_unlock_irqrestore(&csi->lock, flags);
}
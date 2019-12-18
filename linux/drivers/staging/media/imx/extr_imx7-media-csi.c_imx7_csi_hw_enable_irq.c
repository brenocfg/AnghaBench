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
typedef  int /*<<< orphan*/  u32 ;
struct imx7_csi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_EOF_INT_EN ; 
 int /*<<< orphan*/  BIT_FB1_DMA_DONE_INTEN ; 
 int /*<<< orphan*/  BIT_FB2_DMA_DONE_INTEN ; 
 int /*<<< orphan*/  BIT_RFF_OR_INT ; 
 int /*<<< orphan*/  BIT_SOF_INTEN ; 
 int /*<<< orphan*/  CSI_CSICR1 ; 
 int /*<<< orphan*/  imx7_csi_reg_read (struct imx7_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx7_csi_reg_write (struct imx7_csi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx7_csi_hw_enable_irq(struct imx7_csi *csi)
{
	u32 cr1 = imx7_csi_reg_read(csi, CSI_CSICR1);

	cr1 |= BIT_SOF_INTEN;
	cr1 |= BIT_RFF_OR_INT;

	/* still capture needs DMA interrupt */
	cr1 |= BIT_FB1_DMA_DONE_INTEN;
	cr1 |= BIT_FB2_DMA_DONE_INTEN;

	cr1 |= BIT_EOF_INT_EN;

	imx7_csi_reg_write(csi, cr1, CSI_CSICR1);
}
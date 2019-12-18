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
struct imx7_csi {int dummy; } ;

/* Variables and functions */
 int BIT_CLR_RXFIFO ; 
 int BIT_FCC ; 
 int /*<<< orphan*/  CSI_CSICR1 ; 
 int imx7_csi_reg_read (struct imx7_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx7_csi_reg_write (struct imx7_csi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx7_csi_rx_fifo_clear(struct imx7_csi *csi)
{
	u32 cr1;

	cr1 = imx7_csi_reg_read(csi, CSI_CSICR1);
	imx7_csi_reg_write(csi, cr1 & ~BIT_FCC, CSI_CSICR1);
	cr1 = imx7_csi_reg_read(csi, CSI_CSICR1);
	imx7_csi_reg_write(csi, cr1 | BIT_CLR_RXFIFO, CSI_CSICR1);

	cr1 = imx7_csi_reg_read(csi, CSI_CSICR1);
	imx7_csi_reg_write(csi, cr1 | BIT_FCC, CSI_CSICR1);
}
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
struct imx7_csi {int dummy; } ;

/* Variables and functions */
 unsigned int BIT_DMA_REFLASH_RFF ; 
 int BIT_FCC ; 
 int BIT_GCLK_MODE ; 
 int BIT_HSYNC_POL ; 
 int BIT_MCLKEN ; 
 int BIT_REDGE ; 
 int BIT_SOF_POL ; 
 int /*<<< orphan*/  CSI_CSICR1 ; 
 int /*<<< orphan*/  CSI_CSICR3 ; 
 int /*<<< orphan*/  CSI_CSIIMAG_PARA ; 
 int SHIFT_MCLKDIV ; 
 int /*<<< orphan*/  imx7_csi_reg_write (struct imx7_csi*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx7_csi_init_interface(struct imx7_csi *csi)
{
	unsigned int val = 0;
	unsigned int imag_para;

	val = BIT_SOF_POL | BIT_REDGE | BIT_GCLK_MODE | BIT_HSYNC_POL |
		BIT_FCC | 1 << SHIFT_MCLKDIV | BIT_MCLKEN;
	imx7_csi_reg_write(csi, val, CSI_CSICR1);

	imag_para = (800 << 16) | 600;
	imx7_csi_reg_write(csi, imag_para, CSI_CSIIMAG_PARA);

	val = BIT_DMA_REFLASH_RFF;
	imx7_csi_reg_write(csi, val, CSI_CSICR3);
}
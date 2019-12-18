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
 int /*<<< orphan*/  CSI_CSIIMAG_PARA ; 
 int /*<<< orphan*/  CSI_CSIRXCNT ; 
 int /*<<< orphan*/  imx7_csi_dma_reflash (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_reg_write (struct imx7_csi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx7_csi_set_imagpara(struct imx7_csi *csi, int width, int height)
{
	int imag_para;
	int rx_count;

	rx_count = (width * height) >> 2;
	imx7_csi_reg_write(csi, rx_count, CSI_CSIRXCNT);

	imag_para = (width << 16) | height;
	imx7_csi_reg_write(csi, imag_para, CSI_CSIIMAG_PARA);

	/* reflash the embedded DMA controller */
	imx7_csi_dma_reflash(csi);
}
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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_CSIDMASA_FB1 ; 
 int /*<<< orphan*/  CSI_CSIDMASA_FB2 ; 
 int /*<<< orphan*/  imx7_csi_reg_write (struct imx7_csi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx7_csi_update_buf(struct imx7_csi *csi, dma_addr_t phys,
				int buf_num)
{
	if (buf_num == 1)
		imx7_csi_reg_write(csi, phys, CSI_CSIDMASA_FB2);
	else
		imx7_csi_reg_write(csi, phys, CSI_CSIDMASA_FB1);
}
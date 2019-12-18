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
 int /*<<< orphan*/  BIT_CSI_HW_ENABLE ; 
 int /*<<< orphan*/  CSI_CSICR18 ; 
 int /*<<< orphan*/  imx7_csi_reg_read (struct imx7_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx7_csi_reg_write (struct imx7_csi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx7_csi_hw_enable(struct imx7_csi *csi)
{
	u32 cr = imx7_csi_reg_read(csi, CSI_CSICR18);

	cr |= BIT_CSI_HW_ENABLE;

	imx7_csi_reg_write(csi, cr, CSI_CSICR18);
}
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
struct isp_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  IRQ0ENABLE ; 
 int /*<<< orphan*/  IRQ0STATUS ; 
 int /*<<< orphan*/  ISP_PRINT_REGISTER (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCR ; 
 int /*<<< orphan*/  SBL_PRINT_REGISTER (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDR_REQ_EXP ; 
 int /*<<< orphan*/  SYSCONFIG ; 
 int /*<<< orphan*/  SYSSTATUS ; 
 int /*<<< orphan*/  TCTRL_CTRL ; 
 int /*<<< orphan*/  TCTRL_FRAME ; 
 int /*<<< orphan*/  TCTRL_GRESET_LENGTH ; 
 int /*<<< orphan*/  TCTRL_PSTRB_DELAY ; 
 int /*<<< orphan*/  TCTRL_PSTRB_LENGTH ; 
 int /*<<< orphan*/  TCTRL_PSTRB_REPLAY ; 
 int /*<<< orphan*/  TCTRL_SHUT_DELAY ; 
 int /*<<< orphan*/  TCTRL_SHUT_LENGTH ; 
 int /*<<< orphan*/  TCTRL_STRB_DELAY ; 
 int /*<<< orphan*/  TCTRL_STRB_LENGTH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

void omap3isp_print_status(struct isp_device *isp)
{
	dev_dbg(isp->dev, "-------------ISP Register dump--------------\n");

	ISP_PRINT_REGISTER(isp, SYSCONFIG);
	ISP_PRINT_REGISTER(isp, SYSSTATUS);
	ISP_PRINT_REGISTER(isp, IRQ0ENABLE);
	ISP_PRINT_REGISTER(isp, IRQ0STATUS);
	ISP_PRINT_REGISTER(isp, TCTRL_GRESET_LENGTH);
	ISP_PRINT_REGISTER(isp, TCTRL_PSTRB_REPLAY);
	ISP_PRINT_REGISTER(isp, CTRL);
	ISP_PRINT_REGISTER(isp, TCTRL_CTRL);
	ISP_PRINT_REGISTER(isp, TCTRL_FRAME);
	ISP_PRINT_REGISTER(isp, TCTRL_PSTRB_DELAY);
	ISP_PRINT_REGISTER(isp, TCTRL_STRB_DELAY);
	ISP_PRINT_REGISTER(isp, TCTRL_SHUT_DELAY);
	ISP_PRINT_REGISTER(isp, TCTRL_PSTRB_LENGTH);
	ISP_PRINT_REGISTER(isp, TCTRL_STRB_LENGTH);
	ISP_PRINT_REGISTER(isp, TCTRL_SHUT_LENGTH);

	SBL_PRINT_REGISTER(isp, PCR);
	SBL_PRINT_REGISTER(isp, SDR_REQ_EXP);

	dev_dbg(isp->dev, "--------------------------------------------\n");
}
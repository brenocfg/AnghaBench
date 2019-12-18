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
struct isp_ccp2_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCP2_PRINT_REGISTER (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  LC01_IRQENABLE ; 
 int /*<<< orphan*/  LC01_IRQSTATUS ; 
 int /*<<< orphan*/  LC23_IRQENABLE ; 
 int /*<<< orphan*/  LC23_IRQSTATUS ; 
 int /*<<< orphan*/  LCM_CTRL ; 
 int /*<<< orphan*/  LCM_DST_ADDR ; 
 int /*<<< orphan*/  LCM_DST_OFST ; 
 int /*<<< orphan*/  LCM_HSIZE ; 
 int /*<<< orphan*/  LCM_IRQENABLE ; 
 int /*<<< orphan*/  LCM_IRQSTATUS ; 
 int /*<<< orphan*/  LCM_PREFETCH ; 
 int /*<<< orphan*/  LCM_SRC_ADDR ; 
 int /*<<< orphan*/  LCM_SRC_OFST ; 
 int /*<<< orphan*/  LCM_VSIZE ; 
 int /*<<< orphan*/  LCx_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCx_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCx_DAT_OFST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCx_DAT_PING_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCx_DAT_PONG_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCx_DAT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCx_DAT_START (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCx_EOF_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCx_SOF_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCx_STAT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCx_STAT_START (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCONFIG ; 
 int /*<<< orphan*/  SYSSTATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct isp_device* to_isp_device (struct isp_ccp2_device*) ; 

__attribute__((used)) static void ccp2_print_status(struct isp_ccp2_device *ccp2)
{
	struct isp_device *isp = to_isp_device(ccp2);

	dev_dbg(isp->dev, "-------------CCP2 Register dump-------------\n");

	CCP2_PRINT_REGISTER(isp, SYSCONFIG);
	CCP2_PRINT_REGISTER(isp, SYSSTATUS);
	CCP2_PRINT_REGISTER(isp, LC01_IRQENABLE);
	CCP2_PRINT_REGISTER(isp, LC01_IRQSTATUS);
	CCP2_PRINT_REGISTER(isp, LC23_IRQENABLE);
	CCP2_PRINT_REGISTER(isp, LC23_IRQSTATUS);
	CCP2_PRINT_REGISTER(isp, LCM_IRQENABLE);
	CCP2_PRINT_REGISTER(isp, LCM_IRQSTATUS);
	CCP2_PRINT_REGISTER(isp, CTRL);
	CCP2_PRINT_REGISTER(isp, LCx_CTRL(0));
	CCP2_PRINT_REGISTER(isp, LCx_CODE(0));
	CCP2_PRINT_REGISTER(isp, LCx_STAT_START(0));
	CCP2_PRINT_REGISTER(isp, LCx_STAT_SIZE(0));
	CCP2_PRINT_REGISTER(isp, LCx_SOF_ADDR(0));
	CCP2_PRINT_REGISTER(isp, LCx_EOF_ADDR(0));
	CCP2_PRINT_REGISTER(isp, LCx_DAT_START(0));
	CCP2_PRINT_REGISTER(isp, LCx_DAT_SIZE(0));
	CCP2_PRINT_REGISTER(isp, LCx_DAT_PING_ADDR(0));
	CCP2_PRINT_REGISTER(isp, LCx_DAT_PONG_ADDR(0));
	CCP2_PRINT_REGISTER(isp, LCx_DAT_OFST(0));
	CCP2_PRINT_REGISTER(isp, LCM_CTRL);
	CCP2_PRINT_REGISTER(isp, LCM_VSIZE);
	CCP2_PRINT_REGISTER(isp, LCM_HSIZE);
	CCP2_PRINT_REGISTER(isp, LCM_PREFETCH);
	CCP2_PRINT_REGISTER(isp, LCM_SRC_ADDR);
	CCP2_PRINT_REGISTER(isp, LCM_SRC_OFST);
	CCP2_PRINT_REGISTER(isp, LCM_DST_ADDR);
	CCP2_PRINT_REGISTER(isp, LCM_DST_OFST);

	dev_dbg(isp->dev, "--------------------------------------------\n");
}
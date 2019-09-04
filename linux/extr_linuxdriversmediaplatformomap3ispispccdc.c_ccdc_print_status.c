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
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALAW ; 
 int /*<<< orphan*/  BLKCMP ; 
 int /*<<< orphan*/  CCDC_PRINT_REGISTER (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG ; 
 int /*<<< orphan*/  CLAMP ; 
 int /*<<< orphan*/  COLPTN ; 
 int /*<<< orphan*/  CULLING ; 
 int /*<<< orphan*/  DCSUB ; 
 int /*<<< orphan*/  FMTCFG ; 
 int /*<<< orphan*/  FMT_HORZ ; 
 int /*<<< orphan*/  FMT_VERT ; 
 int /*<<< orphan*/  FPC ; 
 int /*<<< orphan*/  FPC_ADDR ; 
 int /*<<< orphan*/  HD_VD_WID ; 
 int /*<<< orphan*/  HORZ_INFO ; 
 int /*<<< orphan*/  HSIZE_OFF ; 
 int /*<<< orphan*/  LSC_CONFIG ; 
 int /*<<< orphan*/  LSC_INITIAL ; 
 int /*<<< orphan*/  LSC_TABLE_BASE ; 
 int /*<<< orphan*/  LSC_TABLE_OFFSET ; 
 int /*<<< orphan*/  PCR ; 
 int /*<<< orphan*/  PIX_LINES ; 
 int /*<<< orphan*/  PRGEVEN0 ; 
 int /*<<< orphan*/  PRGEVEN1 ; 
 int /*<<< orphan*/  PRGODD0 ; 
 int /*<<< orphan*/  PRGODD1 ; 
 int /*<<< orphan*/  REC656IF ; 
 int /*<<< orphan*/  SDOFST ; 
 int /*<<< orphan*/  SDR_ADDR ; 
 int /*<<< orphan*/  SYN_MODE ; 
 int /*<<< orphan*/  VDINT ; 
 int /*<<< orphan*/  VERT_LINES ; 
 int /*<<< orphan*/  VERT_START ; 
 int /*<<< orphan*/  VP_OUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 

__attribute__((used)) static void ccdc_print_status(struct isp_ccdc_device *ccdc)
{
	struct isp_device *isp = to_isp_device(ccdc);

	dev_dbg(isp->dev, "-------------CCDC Register dump-------------\n");

	CCDC_PRINT_REGISTER(isp, PCR);
	CCDC_PRINT_REGISTER(isp, SYN_MODE);
	CCDC_PRINT_REGISTER(isp, HD_VD_WID);
	CCDC_PRINT_REGISTER(isp, PIX_LINES);
	CCDC_PRINT_REGISTER(isp, HORZ_INFO);
	CCDC_PRINT_REGISTER(isp, VERT_START);
	CCDC_PRINT_REGISTER(isp, VERT_LINES);
	CCDC_PRINT_REGISTER(isp, CULLING);
	CCDC_PRINT_REGISTER(isp, HSIZE_OFF);
	CCDC_PRINT_REGISTER(isp, SDOFST);
	CCDC_PRINT_REGISTER(isp, SDR_ADDR);
	CCDC_PRINT_REGISTER(isp, CLAMP);
	CCDC_PRINT_REGISTER(isp, DCSUB);
	CCDC_PRINT_REGISTER(isp, COLPTN);
	CCDC_PRINT_REGISTER(isp, BLKCMP);
	CCDC_PRINT_REGISTER(isp, FPC);
	CCDC_PRINT_REGISTER(isp, FPC_ADDR);
	CCDC_PRINT_REGISTER(isp, VDINT);
	CCDC_PRINT_REGISTER(isp, ALAW);
	CCDC_PRINT_REGISTER(isp, REC656IF);
	CCDC_PRINT_REGISTER(isp, CFG);
	CCDC_PRINT_REGISTER(isp, FMTCFG);
	CCDC_PRINT_REGISTER(isp, FMT_HORZ);
	CCDC_PRINT_REGISTER(isp, FMT_VERT);
	CCDC_PRINT_REGISTER(isp, PRGEVEN0);
	CCDC_PRINT_REGISTER(isp, PRGEVEN1);
	CCDC_PRINT_REGISTER(isp, PRGODD0);
	CCDC_PRINT_REGISTER(isp, PRGODD1);
	CCDC_PRINT_REGISTER(isp, VP_OUT);
	CCDC_PRINT_REGISTER(isp, LSC_CONFIG);
	CCDC_PRINT_REGISTER(isp, LSC_INITIAL);
	CCDC_PRINT_REGISTER(isp, LSC_TABLE_BASE);
	CCDC_PRINT_REGISTER(isp, LSC_TABLE_OFFSET);

	dev_dbg(isp->dev, "--------------------------------------------\n");
}
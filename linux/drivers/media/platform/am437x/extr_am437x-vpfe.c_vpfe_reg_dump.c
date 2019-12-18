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
struct vpfe_device {int dummy; } ;
struct vpfe_ccdc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPFE_ALAW ; 
 int /*<<< orphan*/  VPFE_BLKCMP ; 
 int /*<<< orphan*/  VPFE_CLAMP ; 
 int /*<<< orphan*/  VPFE_COLPTN ; 
 int /*<<< orphan*/  VPFE_DCSUB ; 
 int /*<<< orphan*/  VPFE_HORZ_INFO ; 
 int /*<<< orphan*/  VPFE_HSIZE_OFF ; 
 int /*<<< orphan*/  VPFE_SDOFST ; 
 int /*<<< orphan*/  VPFE_SYNMODE ; 
 int /*<<< orphan*/  VPFE_VERT_LINES ; 
 int /*<<< orphan*/  VPFE_VERT_START ; 
 struct vpfe_device* to_vpfe (struct vpfe_ccdc*) ; 
 int /*<<< orphan*/  vpfe_dbg (int,struct vpfe_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpfe_reg_read (struct vpfe_ccdc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpfe_reg_dump(struct vpfe_ccdc *ccdc)
{
	struct vpfe_device *vpfe = to_vpfe(ccdc);

	vpfe_dbg(3, vpfe, "ALAW: 0x%x\n", vpfe_reg_read(ccdc, VPFE_ALAW));
	vpfe_dbg(3, vpfe, "CLAMP: 0x%x\n", vpfe_reg_read(ccdc, VPFE_CLAMP));
	vpfe_dbg(3, vpfe, "DCSUB: 0x%x\n", vpfe_reg_read(ccdc, VPFE_DCSUB));
	vpfe_dbg(3, vpfe, "BLKCMP: 0x%x\n", vpfe_reg_read(ccdc, VPFE_BLKCMP));
	vpfe_dbg(3, vpfe, "COLPTN: 0x%x\n", vpfe_reg_read(ccdc, VPFE_COLPTN));
	vpfe_dbg(3, vpfe, "SDOFST: 0x%x\n", vpfe_reg_read(ccdc, VPFE_SDOFST));
	vpfe_dbg(3, vpfe, "SYN_MODE: 0x%x\n",
		 vpfe_reg_read(ccdc, VPFE_SYNMODE));
	vpfe_dbg(3, vpfe, "HSIZE_OFF: 0x%x\n",
		 vpfe_reg_read(ccdc, VPFE_HSIZE_OFF));
	vpfe_dbg(3, vpfe, "HORZ_INFO: 0x%x\n",
		 vpfe_reg_read(ccdc, VPFE_HORZ_INFO));
	vpfe_dbg(3, vpfe, "VERT_START: 0x%x\n",
		 vpfe_reg_read(ccdc, VPFE_VERT_START));
	vpfe_dbg(3, vpfe, "VERT_LINES: 0x%x\n",
		 vpfe_reg_read(ccdc, VPFE_VERT_LINES));
}
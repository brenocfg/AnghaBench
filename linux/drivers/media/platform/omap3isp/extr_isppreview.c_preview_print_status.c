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
struct isp_prev_device {int dummy; } ;
struct isp_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVE ; 
 int /*<<< orphan*/  BLKADJOFF ; 
 int /*<<< orphan*/  CDC_THR0 ; 
 int /*<<< orphan*/  CDC_THR1 ; 
 int /*<<< orphan*/  CDC_THR2 ; 
 int /*<<< orphan*/  CDC_THR3 ; 
 int /*<<< orphan*/  CFA ; 
 int /*<<< orphan*/  CNT_BRT ; 
 int /*<<< orphan*/  CSC0 ; 
 int /*<<< orphan*/  CSC1 ; 
 int /*<<< orphan*/  CSC2 ; 
 int /*<<< orphan*/  CSC_OFFSET ; 
 int /*<<< orphan*/  CSUP ; 
 int /*<<< orphan*/  DRKF_OFFSET ; 
 int /*<<< orphan*/  DSDR_ADDR ; 
 int /*<<< orphan*/  HMED ; 
 int /*<<< orphan*/  HORZ_INFO ; 
 int /*<<< orphan*/  NF ; 
 int /*<<< orphan*/  PCR ; 
 int /*<<< orphan*/  PREV_PRINT_REGISTER (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADR_OFFSET ; 
 int /*<<< orphan*/  RGB_MAT1 ; 
 int /*<<< orphan*/  RGB_MAT2 ; 
 int /*<<< orphan*/  RGB_MAT3 ; 
 int /*<<< orphan*/  RGB_MAT4 ; 
 int /*<<< orphan*/  RGB_MAT5 ; 
 int /*<<< orphan*/  RGB_OFF1 ; 
 int /*<<< orphan*/  RGB_OFF2 ; 
 int /*<<< orphan*/  RSDR_ADDR ; 
 int /*<<< orphan*/  SETUP_YC ; 
 int /*<<< orphan*/  SET_TBL_ADDR ; 
 int /*<<< orphan*/  VERT_INFO ; 
 int /*<<< orphan*/  WADD_OFFSET ; 
 int /*<<< orphan*/  WBGAIN ; 
 int /*<<< orphan*/  WBSEL ; 
 int /*<<< orphan*/  WB_DGAIN ; 
 int /*<<< orphan*/  WSDR_ADDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static void preview_print_status(struct isp_prev_device *prev)
{
	struct isp_device *isp = to_isp_device(prev);

	dev_dbg(isp->dev, "-------------Preview Register dump----------\n");

	PREV_PRINT_REGISTER(isp, PCR);
	PREV_PRINT_REGISTER(isp, HORZ_INFO);
	PREV_PRINT_REGISTER(isp, VERT_INFO);
	PREV_PRINT_REGISTER(isp, RSDR_ADDR);
	PREV_PRINT_REGISTER(isp, RADR_OFFSET);
	PREV_PRINT_REGISTER(isp, DSDR_ADDR);
	PREV_PRINT_REGISTER(isp, DRKF_OFFSET);
	PREV_PRINT_REGISTER(isp, WSDR_ADDR);
	PREV_PRINT_REGISTER(isp, WADD_OFFSET);
	PREV_PRINT_REGISTER(isp, AVE);
	PREV_PRINT_REGISTER(isp, HMED);
	PREV_PRINT_REGISTER(isp, NF);
	PREV_PRINT_REGISTER(isp, WB_DGAIN);
	PREV_PRINT_REGISTER(isp, WBGAIN);
	PREV_PRINT_REGISTER(isp, WBSEL);
	PREV_PRINT_REGISTER(isp, CFA);
	PREV_PRINT_REGISTER(isp, BLKADJOFF);
	PREV_PRINT_REGISTER(isp, RGB_MAT1);
	PREV_PRINT_REGISTER(isp, RGB_MAT2);
	PREV_PRINT_REGISTER(isp, RGB_MAT3);
	PREV_PRINT_REGISTER(isp, RGB_MAT4);
	PREV_PRINT_REGISTER(isp, RGB_MAT5);
	PREV_PRINT_REGISTER(isp, RGB_OFF1);
	PREV_PRINT_REGISTER(isp, RGB_OFF2);
	PREV_PRINT_REGISTER(isp, CSC0);
	PREV_PRINT_REGISTER(isp, CSC1);
	PREV_PRINT_REGISTER(isp, CSC2);
	PREV_PRINT_REGISTER(isp, CSC_OFFSET);
	PREV_PRINT_REGISTER(isp, CNT_BRT);
	PREV_PRINT_REGISTER(isp, CSUP);
	PREV_PRINT_REGISTER(isp, SETUP_YC);
	PREV_PRINT_REGISTER(isp, SET_TBL_ADDR);
	PREV_PRINT_REGISTER(isp, CDC_THR0);
	PREV_PRINT_REGISTER(isp, CDC_THR1);
	PREV_PRINT_REGISTER(isp, CDC_THR2);
	PREV_PRINT_REGISTER(isp, CDC_THR3);

	dev_dbg(isp->dev, "--------------------------------------------\n");
}
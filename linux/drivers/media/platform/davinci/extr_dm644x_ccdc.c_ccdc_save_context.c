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

/* Variables and functions */
 int CCDC_ALAW ; 
 int CCDC_BLKCMP ; 
 int CCDC_CCDCFG ; 
 int CCDC_CLAMP ; 
 int CCDC_COLPTN ; 
 int CCDC_CULLING ; 
 int CCDC_DCSUB ; 
 int CCDC_FMTCFG ; 
 int CCDC_FMT_ADDR0 ; 
 int CCDC_FMT_ADDR1 ; 
 int CCDC_FMT_ADDR2 ; 
 int CCDC_FMT_ADDR3 ; 
 int CCDC_FMT_ADDR4 ; 
 int CCDC_FMT_ADDR5 ; 
 int CCDC_FMT_ADDR6 ; 
 int CCDC_FMT_ADDR7 ; 
 int CCDC_FMT_HORZ ; 
 int CCDC_FMT_VERT ; 
 int CCDC_FPC ; 
 int CCDC_FPC_ADDR ; 
 int CCDC_HD_VD_WID ; 
 int CCDC_HORZ_INFO ; 
 int CCDC_HSIZE_OFF ; 
 int CCDC_PCR ; 
 int CCDC_PIX_LINES ; 
 int CCDC_PRGEVEN_0 ; 
 int CCDC_PRGEVEN_1 ; 
 int CCDC_PRGODD_0 ; 
 int CCDC_PRGODD_1 ; 
 int CCDC_REC656IF ; 
 int CCDC_SDOFST ; 
 int CCDC_SDR_ADDR ; 
 int CCDC_SYN_MODE ; 
 int CCDC_VDINT ; 
 int CCDC_VERT_LINES ; 
 int CCDC_VERT_START ; 
 int CCDC_VP_OUT ; 
 int /*<<< orphan*/ * ccdc_ctx ; 
 int /*<<< orphan*/  regr (int) ; 

__attribute__((used)) static void ccdc_save_context(void)
{
	ccdc_ctx[CCDC_PCR >> 2] = regr(CCDC_PCR);
	ccdc_ctx[CCDC_SYN_MODE >> 2] = regr(CCDC_SYN_MODE);
	ccdc_ctx[CCDC_HD_VD_WID >> 2] = regr(CCDC_HD_VD_WID);
	ccdc_ctx[CCDC_PIX_LINES >> 2] = regr(CCDC_PIX_LINES);
	ccdc_ctx[CCDC_HORZ_INFO >> 2] = regr(CCDC_HORZ_INFO);
	ccdc_ctx[CCDC_VERT_START >> 2] = regr(CCDC_VERT_START);
	ccdc_ctx[CCDC_VERT_LINES >> 2] = regr(CCDC_VERT_LINES);
	ccdc_ctx[CCDC_CULLING >> 2] = regr(CCDC_CULLING);
	ccdc_ctx[CCDC_HSIZE_OFF >> 2] = regr(CCDC_HSIZE_OFF);
	ccdc_ctx[CCDC_SDOFST >> 2] = regr(CCDC_SDOFST);
	ccdc_ctx[CCDC_SDR_ADDR >> 2] = regr(CCDC_SDR_ADDR);
	ccdc_ctx[CCDC_CLAMP >> 2] = regr(CCDC_CLAMP);
	ccdc_ctx[CCDC_DCSUB >> 2] = regr(CCDC_DCSUB);
	ccdc_ctx[CCDC_COLPTN >> 2] = regr(CCDC_COLPTN);
	ccdc_ctx[CCDC_BLKCMP >> 2] = regr(CCDC_BLKCMP);
	ccdc_ctx[CCDC_FPC >> 2] = regr(CCDC_FPC);
	ccdc_ctx[CCDC_FPC_ADDR >> 2] = regr(CCDC_FPC_ADDR);
	ccdc_ctx[CCDC_VDINT >> 2] = regr(CCDC_VDINT);
	ccdc_ctx[CCDC_ALAW >> 2] = regr(CCDC_ALAW);
	ccdc_ctx[CCDC_REC656IF >> 2] = regr(CCDC_REC656IF);
	ccdc_ctx[CCDC_CCDCFG >> 2] = regr(CCDC_CCDCFG);
	ccdc_ctx[CCDC_FMTCFG >> 2] = regr(CCDC_FMTCFG);
	ccdc_ctx[CCDC_FMT_HORZ >> 2] = regr(CCDC_FMT_HORZ);
	ccdc_ctx[CCDC_FMT_VERT >> 2] = regr(CCDC_FMT_VERT);
	ccdc_ctx[CCDC_FMT_ADDR0 >> 2] = regr(CCDC_FMT_ADDR0);
	ccdc_ctx[CCDC_FMT_ADDR1 >> 2] = regr(CCDC_FMT_ADDR1);
	ccdc_ctx[CCDC_FMT_ADDR2 >> 2] = regr(CCDC_FMT_ADDR2);
	ccdc_ctx[CCDC_FMT_ADDR3 >> 2] = regr(CCDC_FMT_ADDR3);
	ccdc_ctx[CCDC_FMT_ADDR4 >> 2] = regr(CCDC_FMT_ADDR4);
	ccdc_ctx[CCDC_FMT_ADDR5 >> 2] = regr(CCDC_FMT_ADDR5);
	ccdc_ctx[CCDC_FMT_ADDR6 >> 2] = regr(CCDC_FMT_ADDR6);
	ccdc_ctx[CCDC_FMT_ADDR7 >> 2] = regr(CCDC_FMT_ADDR7);
	ccdc_ctx[CCDC_PRGEVEN_0 >> 2] = regr(CCDC_PRGEVEN_0);
	ccdc_ctx[CCDC_PRGEVEN_1 >> 2] = regr(CCDC_PRGEVEN_1);
	ccdc_ctx[CCDC_PRGODD_0 >> 2] = regr(CCDC_PRGODD_0);
	ccdc_ctx[CCDC_PRGODD_1 >> 2] = regr(CCDC_PRGODD_1);
	ccdc_ctx[CCDC_VP_OUT >> 2] = regr(CCDC_VP_OUT);
}
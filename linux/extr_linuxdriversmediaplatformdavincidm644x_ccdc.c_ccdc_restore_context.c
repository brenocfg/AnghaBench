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
 int /*<<< orphan*/  regw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ccdc_restore_context(void)
{
	regw(ccdc_ctx[CCDC_SYN_MODE >> 2], CCDC_SYN_MODE);
	regw(ccdc_ctx[CCDC_HD_VD_WID >> 2], CCDC_HD_VD_WID);
	regw(ccdc_ctx[CCDC_PIX_LINES >> 2], CCDC_PIX_LINES);
	regw(ccdc_ctx[CCDC_HORZ_INFO >> 2], CCDC_HORZ_INFO);
	regw(ccdc_ctx[CCDC_VERT_START >> 2], CCDC_VERT_START);
	regw(ccdc_ctx[CCDC_VERT_LINES >> 2], CCDC_VERT_LINES);
	regw(ccdc_ctx[CCDC_CULLING >> 2], CCDC_CULLING);
	regw(ccdc_ctx[CCDC_HSIZE_OFF >> 2], CCDC_HSIZE_OFF);
	regw(ccdc_ctx[CCDC_SDOFST >> 2], CCDC_SDOFST);
	regw(ccdc_ctx[CCDC_SDR_ADDR >> 2], CCDC_SDR_ADDR);
	regw(ccdc_ctx[CCDC_CLAMP >> 2], CCDC_CLAMP);
	regw(ccdc_ctx[CCDC_DCSUB >> 2], CCDC_DCSUB);
	regw(ccdc_ctx[CCDC_COLPTN >> 2], CCDC_COLPTN);
	regw(ccdc_ctx[CCDC_BLKCMP >> 2], CCDC_BLKCMP);
	regw(ccdc_ctx[CCDC_FPC >> 2], CCDC_FPC);
	regw(ccdc_ctx[CCDC_FPC_ADDR >> 2], CCDC_FPC_ADDR);
	regw(ccdc_ctx[CCDC_VDINT >> 2], CCDC_VDINT);
	regw(ccdc_ctx[CCDC_ALAW >> 2], CCDC_ALAW);
	regw(ccdc_ctx[CCDC_REC656IF >> 2], CCDC_REC656IF);
	regw(ccdc_ctx[CCDC_CCDCFG >> 2], CCDC_CCDCFG);
	regw(ccdc_ctx[CCDC_FMTCFG >> 2], CCDC_FMTCFG);
	regw(ccdc_ctx[CCDC_FMT_HORZ >> 2], CCDC_FMT_HORZ);
	regw(ccdc_ctx[CCDC_FMT_VERT >> 2], CCDC_FMT_VERT);
	regw(ccdc_ctx[CCDC_FMT_ADDR0 >> 2], CCDC_FMT_ADDR0);
	regw(ccdc_ctx[CCDC_FMT_ADDR1 >> 2], CCDC_FMT_ADDR1);
	regw(ccdc_ctx[CCDC_FMT_ADDR2 >> 2], CCDC_FMT_ADDR2);
	regw(ccdc_ctx[CCDC_FMT_ADDR3 >> 2], CCDC_FMT_ADDR3);
	regw(ccdc_ctx[CCDC_FMT_ADDR4 >> 2], CCDC_FMT_ADDR4);
	regw(ccdc_ctx[CCDC_FMT_ADDR5 >> 2], CCDC_FMT_ADDR5);
	regw(ccdc_ctx[CCDC_FMT_ADDR6 >> 2], CCDC_FMT_ADDR6);
	regw(ccdc_ctx[CCDC_FMT_ADDR7 >> 2], CCDC_FMT_ADDR7);
	regw(ccdc_ctx[CCDC_PRGEVEN_0 >> 2], CCDC_PRGEVEN_0);
	regw(ccdc_ctx[CCDC_PRGEVEN_1 >> 2], CCDC_PRGEVEN_1);
	regw(ccdc_ctx[CCDC_PRGODD_0 >> 2], CCDC_PRGODD_0);
	regw(ccdc_ctx[CCDC_PRGODD_1 >> 2], CCDC_PRGODD_1);
	regw(ccdc_ctx[CCDC_VP_OUT >> 2], CCDC_VP_OUT);
	regw(ccdc_ctx[CCDC_PCR >> 2], CCDC_PCR);
}
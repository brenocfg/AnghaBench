#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  Adapter; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int BIT10 ; 
 int BIT7 ; 
 int BIT8 ; 
 int BIT9 ; 
 scalar_t__ ODM_REG_FPGA0_IQK_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH3_TO_TH0_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH7_TO_TH4_11N ; 
 scalar_t__ ODM_REG_NHM_TH9_TH10_11N ; 
 scalar_t__ ODM_REG_NHM_TIMER_11N ; 
 scalar_t__ ODM_REG_OFDM_FA_RSTC_11N ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int bMaskByte0 ; 
 int /*<<< orphan*/  rtw_write16 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void odm_NHMCounterStatisticsInit(void *pDM_VOID)
{
	PDM_ODM_T		pDM_Odm = (PDM_ODM_T)pDM_VOID;

	/* PHY parameters initialize for n series */
	rtw_write16(pDM_Odm->Adapter, ODM_REG_NHM_TIMER_11N+2, 0x2710);	/* 0x894[31:16]= 0x2710	Time duration for NHM unit: 4us, 0x2710 =40ms */
	/* rtw_write16(pDM_Odm->Adapter, ODM_REG_NHM_TIMER_11N+2, 0x4e20);	0x894[31:16]= 0x4e20	Time duration for NHM unit: 4us, 0x4e20 =80ms */
	rtw_write16(pDM_Odm->Adapter, ODM_REG_NHM_TH9_TH10_11N+2, 0xffff);	/* 0x890[31:16]= 0xffff	th_9, th_10 */
	/* rtw_write32(pDM_Odm->Adapter, ODM_REG_NHM_TH3_TO_TH0_11N, 0xffffff5c);	0x898 = 0xffffff5c		th_3, th_2, th_1, th_0 */
	rtw_write32(pDM_Odm->Adapter, ODM_REG_NHM_TH3_TO_TH0_11N, 0xffffff52);	/* 0x898 = 0xffffff52		th_3, th_2, th_1, th_0 */
	rtw_write32(pDM_Odm->Adapter, ODM_REG_NHM_TH7_TO_TH4_11N, 0xffffffff);	/* 0x89c = 0xffffffff		th_7, th_6, th_5, th_4 */
	PHY_SetBBReg(pDM_Odm->Adapter, ODM_REG_FPGA0_IQK_11N, bMaskByte0, 0xff);		/* 0xe28[7:0]= 0xff		th_8 */
	PHY_SetBBReg(pDM_Odm->Adapter, ODM_REG_NHM_TH9_TH10_11N, BIT10|BIT9|BIT8, 0x7);	/* 0x890[9:8]=3			enable CCX */
	PHY_SetBBReg(pDM_Odm->Adapter, ODM_REG_OFDM_FA_RSTC_11N, BIT7, 0x1);		/* 0xc0c[7]= 1			max power among all RX ants */
}
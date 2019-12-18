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
struct mtk_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_RTC_CTL ; 
 int /*<<< orphan*/  MTK_RTC_DEBNCE ; 
 int /*<<< orphan*/  MTK_RTC_KEY ; 
 int /*<<< orphan*/  MTK_RTC_PROT1 ; 
 int /*<<< orphan*/  MTK_RTC_PROT2 ; 
 int /*<<< orphan*/  MTK_RTC_PROT3 ; 
 int /*<<< orphan*/  MTK_RTC_PROT4 ; 
 int /*<<< orphan*/  MTK_RTC_PWRCHK1 ; 
 int /*<<< orphan*/  MTK_RTC_PWRCHK2 ; 
 int /*<<< orphan*/  RTC_DEBNCE_MASK ; 
 int /*<<< orphan*/  RTC_KEY_MAGIC ; 
 int /*<<< orphan*/  RTC_PROT1_MAGIC ; 
 int /*<<< orphan*/  RTC_PROT2_MAGIC ; 
 int /*<<< orphan*/  RTC_PROT3_MAGIC ; 
 int /*<<< orphan*/  RTC_PROT4_MAGIC ; 
 int /*<<< orphan*/  RTC_PWRCHK1_MAGIC ; 
 int /*<<< orphan*/  RTC_PWRCHK2_MAGIC ; 
 int /*<<< orphan*/  RTC_RC_STOP ; 
 int /*<<< orphan*/  mtk_clr (struct mtk_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_rmw (struct mtk_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_rtc_hw_init(struct mtk_rtc *hw)
{
	/* The setup of the init sequence is for allowing RTC got to work */
	mtk_w32(hw, MTK_RTC_PWRCHK1, RTC_PWRCHK1_MAGIC);
	mtk_w32(hw, MTK_RTC_PWRCHK2, RTC_PWRCHK2_MAGIC);
	mtk_w32(hw, MTK_RTC_KEY, RTC_KEY_MAGIC);
	mtk_w32(hw, MTK_RTC_PROT1, RTC_PROT1_MAGIC);
	mtk_w32(hw, MTK_RTC_PROT2, RTC_PROT2_MAGIC);
	mtk_w32(hw, MTK_RTC_PROT3, RTC_PROT3_MAGIC);
	mtk_w32(hw, MTK_RTC_PROT4, RTC_PROT4_MAGIC);
	mtk_rmw(hw, MTK_RTC_DEBNCE, RTC_DEBNCE_MASK, 0);
	mtk_clr(hw, MTK_RTC_CTL, RTC_RC_STOP);
}
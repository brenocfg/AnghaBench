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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_DPK_AGC_OUT ; 
 int /*<<< orphan*/  RTW_DPK_GL_LARGE ; 
 int /*<<< orphan*/  RTW_DPK_GL_LESS ; 
 int rtw8822c_dpk_pas_read (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int rtw8822c_psd_log2base (int) ; 

__attribute__((used)) static u8 rtw8822c_dpk_agc_loss_chk(struct rtw_dev *rtwdev, u8 path)
{
	u32 loss, loss_db;

	loss = rtw8822c_dpk_pas_read(rtwdev, path);
	if (loss < 0x4000000)
		return RTW_DPK_GL_LESS;
	loss_db = 3 * rtw8822c_psd_log2base(loss >> 13) - 3870;

	if (loss_db > 1000)
		return RTW_DPK_GL_LARGE;
	else if (loss_db < 250)
		return RTW_DPK_GL_LESS;
	else
		return RTW_DPK_AGC_OUT;
}
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
typedef  int u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int DACK_SN_8822C ; 
 int /*<<< orphan*/  __rtw8822c_dac_iq_sort (struct rtw_dev*,int*,int*) ; 

__attribute__((used)) static void rtw8822c_dac_iq_sort(struct rtw_dev *rtwdev, u32 *iv, u32 *qv)
{
	u32 i, j;

	for (i = 0; i < DACK_SN_8822C - 1; i++) {
		for (j = 0; j < (DACK_SN_8822C - 1 - i) ; j++) {
			__rtw8822c_dac_iq_sort(rtwdev, &iv[j], &iv[j + 1]);
			__rtw8822c_dac_iq_sort(rtwdev, &qv[j], &qv[j + 1]);
		}
	}
}
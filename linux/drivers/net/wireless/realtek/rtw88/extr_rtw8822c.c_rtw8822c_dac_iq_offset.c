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

__attribute__((used)) static void rtw8822c_dac_iq_offset(struct rtw_dev *rtwdev, u32 *vec, u32 *val)
{
	u32 p, m, t, i;

	m = 0;
	p = 0;
	for (i = 10; i < DACK_SN_8822C - 10; i++) {
		if (vec[i] > 0x200)
			m = (0x400 - vec[i]) + m;
		else
			p = vec[i] + p;
	}

	if (p > m) {
		t = p - m;
		t = t / (DACK_SN_8822C - 20);
	} else {
		t = m - p;
		t = t / (DACK_SN_8822C - 20);
		if (t != 0x0)
			t = 0x400 - t;
	}

	*val = t;
}
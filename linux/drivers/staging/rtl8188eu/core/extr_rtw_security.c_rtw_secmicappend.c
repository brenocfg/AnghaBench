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
typedef  scalar_t__ u32 ;
struct mic_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_secmicappendbyte (struct mic_data*,int /*<<< orphan*/ ) ; 

void rtw_secmicappend(struct mic_data *pmicdata, u8 *src, u32 nbytes)
{
	/*  This is simple */
	while (nbytes > 0) {
		rtw_secmicappendbyte(pmicdata, *src++);
		nbytes--;
	}
}
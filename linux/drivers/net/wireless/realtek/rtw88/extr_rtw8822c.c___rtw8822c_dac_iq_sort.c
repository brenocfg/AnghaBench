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
 int /*<<< orphan*/  swap_u32 (int*,int*) ; 

__attribute__((used)) static void __rtw8822c_dac_iq_sort(struct rtw_dev *rtwdev, u32 *v1, u32 *v2)
{
	if (*v1 >= 0x200 && *v2 >= 0x200) {
		if (*v1 > *v2)
			swap_u32(v1, v2);
	} else if (*v1 < 0x200 && *v2 < 0x200) {
		if (*v1 > *v2)
			swap_u32(v1, v2);
	} else if (*v1 < 0x200 && *v2 >= 0x200) {
		swap_u32(v1, v2);
	}
}
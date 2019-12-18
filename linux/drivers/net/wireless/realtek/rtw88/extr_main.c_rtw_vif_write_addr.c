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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_vif_write_addr(struct rtw_dev *rtwdev, u32 start, u8 *addr)
{
	int i;

	for (i = 0; i < ETH_ALEN; i++)
		rtw_write8(rtwdev, start + i, addr[i]);
}
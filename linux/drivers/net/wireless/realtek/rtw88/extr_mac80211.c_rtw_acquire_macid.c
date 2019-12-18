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
typedef  unsigned long u8 ;
struct rtw_dev {int /*<<< orphan*/  mac_id_map; } ;

/* Variables and functions */
 unsigned long RTW_MAX_MAC_ID_NUM ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 rtw_acquire_macid(struct rtw_dev *rtwdev)
{
	unsigned long mac_id;

	mac_id = find_first_zero_bit(rtwdev->mac_id_map, RTW_MAX_MAC_ID_NUM);
	if (mac_id < RTW_MAX_MAC_ID_NUM)
		set_bit(mac_id, rtwdev->mac_id_map);

	return mac_id;
}
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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RATEID_IDX_B ; 
 int /*<<< orphan*/  RATEID_IDX_G ; 
 unsigned char WIRELESS_11B ; 

u8 rtw_get_mgntframe_raid(struct adapter *adapter, unsigned char network_type)
{

	u8 raid;
	raid = (network_type & WIRELESS_11B) ? RATEID_IDX_B : RATEID_IDX_G;
	return raid;
}
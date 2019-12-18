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
struct hal_com_data {int dummy; } ;
struct adapter {int hal_data_sz; int /*<<< orphan*/  HalData; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 scalar_t__ is_primary_adapter (struct adapter*) ; 
 int /*<<< orphan*/  vzalloc (int) ; 

u8 rtw_hal_data_init(struct adapter *padapter)
{
	if (is_primary_adapter(padapter)) {	/* if (padapter->isprimary) */
		padapter->hal_data_sz = sizeof(struct hal_com_data);
		padapter->HalData = vzalloc(padapter->hal_data_sz);
		if (!padapter->HalData) {
			DBG_8192C("cannot alloc memory for HAL DATA\n");
			return _FAIL;
		}
	}
	return _SUCCESS;
}
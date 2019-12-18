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
struct adapter {scalar_t__ hal_data_sz; int /*<<< orphan*/ * HalData; } ;

/* Variables and functions */
 scalar_t__ is_primary_adapter (struct adapter*) ; 
 int /*<<< orphan*/  phy_free_filebuf (struct adapter*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void rtw_hal_data_deinit(struct adapter *padapter)
{
	if (is_primary_adapter(padapter)) {	/* if (padapter->isprimary) */
		if (padapter->HalData) {
			phy_free_filebuf(padapter);
			vfree(padapter->HalData);
			padapter->HalData = NULL;
			padapter->hal_data_sz = 0;
		}
	}
}
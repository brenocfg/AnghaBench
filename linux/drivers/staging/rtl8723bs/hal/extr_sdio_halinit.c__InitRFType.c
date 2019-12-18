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
struct hal_com_data {int /*<<< orphan*/  rf_type; int /*<<< orphan*/  rf_chip; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  RF_1T1R ; 
 int /*<<< orphan*/  RF_6052 ; 
 int /*<<< orphan*/  RF_PSEUDO_11N ; 

__attribute__((used)) static void _InitRFType(struct adapter *padapter)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);

#if	DISABLE_BB_RF
	pHalData->rf_chip	= RF_PSEUDO_11N;
	return;
#endif

	pHalData->rf_chip	= RF_6052;

	pHalData->rf_type = RF_1T1R;
	DBG_8192C("Set RF Chip ID to RF_6052 and RF type to 1T1R.\n");
}
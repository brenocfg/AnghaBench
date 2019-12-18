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
struct dm_priv {int dummy; } ;
struct hal_com_data {struct dm_priv dmpriv; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  Init_ODM_ComInfo_8723b (struct adapter*) ; 
 int /*<<< orphan*/  memset (struct dm_priv*,int /*<<< orphan*/ ,int) ; 

void rtl8723b_init_dm_priv(struct adapter *Adapter)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	struct dm_priv *pdmpriv = &pHalData->dmpriv;

	memset(pdmpriv, 0, sizeof(struct dm_priv));
	Init_ODM_ComInfo_8723b(Adapter);
}
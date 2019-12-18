#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  Adapter; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_SetTxPowerLimit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void odm_ConfigBB_TXPWR_LMT_8723B(
	PDM_ODM_T pDM_Odm,
	u8 *Regulation,
	u8 *Band,
	u8 *Bandwidth,
	u8 *RateSection,
	u8 *RfPath,
	u8 *Channel,
	u8 *PowerLimit
)
{
	PHY_SetTxPowerLimit(
		pDM_Odm->Adapter,
		Regulation,
		Band,
		Bandwidth,
		RateSection,
		RfPath,
		Channel,
		PowerLimit
	);
}
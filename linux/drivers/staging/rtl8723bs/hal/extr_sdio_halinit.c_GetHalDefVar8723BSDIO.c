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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;
typedef  enum HAL_DEF_VARIABLE { ____Placeholder_HAL_DEF_VARIABLE } HAL_DEF_VARIABLE ;

/* Variables and functions */
 int /*<<< orphan*/  GetHalDefVar8723B (struct adapter*,int,void*) ; 
#define  HAL_DEF_CURRENT_ANTENNA 130 
#define  HAL_DEF_IS_SUPPORT_ANT_DIV 129 
#define  HW_VAR_MAX_RX_AMPDU_FACTOR 128 
 int /*<<< orphan*/  MAX_AMPDU_FACTOR_16K ; 
 int /*<<< orphan*/  _SUCCESS ; 

__attribute__((used)) static u8 GetHalDefVar8723BSDIO(
	struct adapter *Adapter, enum HAL_DEF_VARIABLE eVariable, void *pValue
)
{
	u8 	bResult = _SUCCESS;

	switch (eVariable) {
	case HAL_DEF_IS_SUPPORT_ANT_DIV:
		break;
	case HAL_DEF_CURRENT_ANTENNA:
		break;
	case HW_VAR_MAX_RX_AMPDU_FACTOR:
		/*  Stanley@BB.SD3 suggests 16K can get stable performance */
		/*  coding by Lucas@20130730 */
		*(u32 *)pValue = MAX_AMPDU_FACTOR_16K;
		break;
	default:
		bResult = GetHalDefVar8723B(Adapter, eVariable, pValue);
		break;
	}

	return bResult;
}
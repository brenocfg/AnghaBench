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
typedef  size_t u8 ;
struct hal_com_data {int /*<<< orphan*/ * noise; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  enum HAL_ODM_VARIABLE { ____Placeholder_HAL_ODM_VARIABLE } HAL_ODM_VARIABLE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*,size_t,int /*<<< orphan*/ ) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
#define  HAL_ODM_NOISE_MONITOR 128 

void GetHalODMVar(
	struct adapter *Adapter,
	enum HAL_ODM_VARIABLE eVariable,
	void *pValue1,
	void *pValue2
)
{
	switch (eVariable) {
#if defined(CONFIG_SIGNAL_DISPLAY_DBM) && defined(CONFIG_BACKGROUND_NOISE_MONITOR)
	case HAL_ODM_NOISE_MONITOR:
		{
			struct hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
			u8 chan = *(u8 *)pValue1;
			*(s16 *)pValue2 = pHalData->noise[chan];
			#ifdef DBG_NOISE_MONITOR
			DBG_8192C("### Noise monitor chan(%d)-noise:%d (dBm) ###\n",
				chan, pHalData->noise[chan]);
			#endif

		}
		break;
#endif/* ifdef CONFIG_BACKGROUND_NOISE_MONITOR */
	default:
		break;
	}
}
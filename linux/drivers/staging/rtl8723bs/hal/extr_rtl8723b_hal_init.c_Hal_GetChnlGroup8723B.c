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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 

__attribute__((used)) static bool Hal_GetChnlGroup8723B(u8 Channel, u8 *pGroup)
{
	bool bIn24G = true;

	if (Channel <= 14) {
		bIn24G = true;

		if (1  <= Channel && Channel <= 2)
			*pGroup = 0;
		else if (3  <= Channel && Channel <= 5)
			*pGroup = 1;
		else if (6  <= Channel && Channel <= 8)
			*pGroup = 2;
		else if (9  <= Channel && Channel <= 11)
			*pGroup = 3;
		else if (12 <= Channel && Channel <= 14)
			*pGroup = 4;
		else {
			RT_TRACE(_module_hci_hal_init_c_, _drv_notice_, ("==>Hal_GetChnlGroup8723B in 2.4 G, but Channel %d in Group not found\n", Channel));
		}
	} else {
		bIn24G = false;

		if (36   <= Channel && Channel <=  42)
			*pGroup = 0;
		else if (44   <= Channel && Channel <=  48)
			*pGroup = 1;
		else if (50   <= Channel && Channel <=  58)
			*pGroup = 2;
		else if (60   <= Channel && Channel <=  64)
			*pGroup = 3;
		else if (100  <= Channel && Channel <= 106)
			*pGroup = 4;
		else if (108  <= Channel && Channel <= 114)
			*pGroup = 5;
		else if (116  <= Channel && Channel <= 122)
			*pGroup = 6;
		else if (124  <= Channel && Channel <= 130)
			*pGroup = 7;
		else if (132  <= Channel && Channel <= 138)
			*pGroup = 8;
		else if (140  <= Channel && Channel <= 144)
			*pGroup = 9;
		else if (149  <= Channel && Channel <= 155)
			*pGroup = 10;
		else if (157  <= Channel && Channel <= 161)
			*pGroup = 11;
		else if (165  <= Channel && Channel <= 171)
			*pGroup = 12;
		else if (173  <= Channel && Channel <= 177)
			*pGroup = 13;
		else {
			RT_TRACE(_module_hci_hal_init_c_, _drv_notice_, ("==>Hal_GetChnlGroup8723B in 5G, but Channel %d in Group not found\n", Channel));
		}

	}
	RT_TRACE(
		_module_hci_hal_init_c_,
		_drv_info_,
		(
			"<==Hal_GetChnlGroup8723B,  (%s) Channel = %d, Group =%d,\n",
			bIn24G ? "2.4G" : "5G",
			Channel,
			*pGroup
		)
	);
	return bIn24G;
}
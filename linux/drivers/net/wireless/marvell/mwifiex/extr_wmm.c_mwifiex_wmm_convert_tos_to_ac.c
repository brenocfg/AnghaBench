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
typedef  size_t u32 ;
struct mwifiex_adapter {int dummy; } ;
typedef  enum mwifiex_wmm_ac_e { ____Placeholder_mwifiex_wmm_ac_e } mwifiex_wmm_ac_e ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
#define  WMM_AC_BE 131 
#define  WMM_AC_BK 130 
#define  WMM_AC_VI 129 
#define  WMM_AC_VO 128 

__attribute__((used)) static enum mwifiex_wmm_ac_e
mwifiex_wmm_convert_tos_to_ac(struct mwifiex_adapter *adapter, u32 tos)
{
	/* Map of TOS UP values to WMM AC */
	static const enum mwifiex_wmm_ac_e tos_to_ac[] = {
		WMM_AC_BE,
		WMM_AC_BK,
		WMM_AC_BK,
		WMM_AC_BE,
		WMM_AC_VI,
		WMM_AC_VI,
		WMM_AC_VO,
		WMM_AC_VO
	};

	if (tos >= ARRAY_SIZE(tos_to_ac))
		return WMM_AC_BE;

	return tos_to_ac[tos];
}
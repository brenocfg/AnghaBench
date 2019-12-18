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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int ANT_B ; 
 scalar_t__ IWL_4165_DEVICE_ID ; 
 unsigned int NVM_SECTION_TYPE_PHY_SKU ; 
 int NVM_SKU_CAP_MIMO_DISABLE ; 

void iwl_nvm_fixups(u32 hw_id, unsigned int section, u8 *data,
		    unsigned int len)
{
#define IWL_4165_DEVICE_ID	0x5501
#define NVM_SKU_CAP_MIMO_DISABLE BIT(5)

	if (section == NVM_SECTION_TYPE_PHY_SKU &&
	    hw_id == IWL_4165_DEVICE_ID && data && len >= 5 &&
	    (data[4] & NVM_SKU_CAP_MIMO_DISABLE))
		/* OTP 0x52 bug work around: it's a 1x1 device */
		data[3] = ANT_B | (ANT_B << 4);
}
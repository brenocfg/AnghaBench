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
 int CHANNEL_MAX_NUMBER_5G ; 
 int* channel5g ; 

__attribute__((used)) static bool _rtl8821ae_phy_get_chnl_index(u8 channel, u8 *chnl_index)
{
	u8 i = 0;
	bool in_24g = true;

	if (channel <= 14) {
		in_24g = true;
		*chnl_index = channel - 1;
	} else {
		in_24g = false;

		for (i = 0; i < CHANNEL_MAX_NUMBER_5G; ++i) {
			if (channel5g[i] == channel) {
				*chnl_index = i;
				return in_24g;
			}
		}
	}
	return in_24g;
}
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
struct ath_hw {int dummy; } ;
struct ath_common {int const* macaddr; int const* bssidmask; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 

__attribute__((used)) static inline bool ath_dynack_bssidmask(struct ath_hw *ah, const u8 *mac)
{
	int i;
	struct ath_common *common = ath9k_hw_common(ah);

	for (i = 0; i < ETH_ALEN; i++) {
		if ((common->macaddr[i] & common->bssidmask[i]) !=
		    (mac[i] & common->bssidmask[i]))
			return false;
	}

	return true;
}
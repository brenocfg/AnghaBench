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
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 

__attribute__((used)) static int ar9561_hw_get_modes_txgain_index(struct ath_hw *ah,
					    struct ath9k_channel *chan)
{
	if (IS_CHAN_2GHZ(chan)) {
		if (IS_CHAN_HT40(chan))
			return 1;
		else
			return 2;
	}

	return 0;
}
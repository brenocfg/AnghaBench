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
struct ath_common {unsigned int clockrate; } ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 

unsigned int
ath5k_hw_clocktoh(struct ath5k_hw *ah, unsigned int clock)
{
	struct ath_common *common = ath5k_hw_common(ah);
	return clock / common->clockrate;
}
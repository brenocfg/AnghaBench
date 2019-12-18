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
typedef  int u32 ;
struct ath_hw {struct ath9k_channel* curchan; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_CHAN_HALF_RATE (struct ath9k_channel const*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel const*) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (struct ath9k_channel const*) ; 

__attribute__((used)) static u32 ath_dynack_get_max_to(struct ath_hw *ah)
{
	const struct ath9k_channel *chan = ah->curchan;

	if (!chan)
		return 300;

	if (IS_CHAN_HT40(chan))
		return 300;
	if (IS_CHAN_HALF_RATE(chan))
		return 750;
	if (IS_CHAN_QUARTER_RATE(chan))
		return 1500;
	return 600;
}
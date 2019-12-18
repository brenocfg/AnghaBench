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
struct ath_nf_limits {int dummy; } ;
struct ath_hw {struct ath_nf_limits nf_5g; struct ath_nf_limits nf_2g; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 

__attribute__((used)) static struct ath_nf_limits *ath9k_hw_get_nf_limits(struct ath_hw *ah,
						    struct ath9k_channel *chan)
{
	struct ath_nf_limits *limit;

	if (!chan || IS_CHAN_2GHZ(chan))
		limit = &ah->nf_2g;
	else
		limit = &ah->nf_5g;

	return limit;
}
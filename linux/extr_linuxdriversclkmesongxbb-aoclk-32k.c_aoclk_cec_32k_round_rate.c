#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct cec_32k_freq_table {long target_rate; } ;
struct TYPE_2__ {long target_rate; } ;

/* Variables and functions */
 TYPE_1__* aoclk_cec_32k_table ; 
 struct cec_32k_freq_table* find_cec_32k_freq (unsigned long,unsigned long) ; 

__attribute__((used)) static long aoclk_cec_32k_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	const struct cec_32k_freq_table *freq = find_cec_32k_freq(rate,
								  *prate);

	/* If invalid return first one */
	if (!freq)
		return aoclk_cec_32k_table[0].target_rate;

	return freq->target_rate;
}
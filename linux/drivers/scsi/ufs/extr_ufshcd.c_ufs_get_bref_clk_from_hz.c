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
typedef  enum ufs_ref_clk_freq { ____Placeholder_ufs_ref_clk_freq } ufs_ref_clk_freq ;
struct TYPE_2__ {long freq_hz; int val; } ;

/* Variables and functions */
 int REF_CLK_FREQ_INVAL ; 
 TYPE_1__* ufs_ref_clk_freqs ; 

__attribute__((used)) static enum ufs_ref_clk_freq
ufs_get_bref_clk_from_hz(unsigned long freq)
{
	int i;

	for (i = 0; ufs_ref_clk_freqs[i].freq_hz; i++)
		if (ufs_ref_clk_freqs[i].freq_hz == freq)
			return ufs_ref_clk_freqs[i].val;

	return REF_CLK_FREQ_INVAL;
}
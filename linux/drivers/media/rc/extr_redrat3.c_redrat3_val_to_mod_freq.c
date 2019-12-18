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
typedef  int u16 ;
struct redrat3_irdata {int /*<<< orphan*/  num_periods; int /*<<< orphan*/  mod_freq_count; } ;

/* Variables and functions */
 int RR3_CLK ; 
 int RR3_CLK_PER_COUNT ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 redrat3_val_to_mod_freq(struct redrat3_irdata *irdata)
{
	u32 mod_freq = 0;
	u16 mod_freq_count = be16_to_cpu(irdata->mod_freq_count);

	if (mod_freq_count != 0)
		mod_freq = (RR3_CLK * be16_to_cpu(irdata->num_periods)) /
			(mod_freq_count * RR3_CLK_PER_COUNT);

	return mod_freq;
}
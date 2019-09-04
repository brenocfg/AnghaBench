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
struct cec_32k_freq_table {unsigned long parent_rate; unsigned long target_rate; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cec_32k_freq_table const*) ; 
 struct cec_32k_freq_table const* aoclk_cec_32k_table ; 

__attribute__((used)) static const struct cec_32k_freq_table *find_cec_32k_freq(unsigned long rate,
							  unsigned long prate)
{
	int i;

	for (i = 0 ; i < ARRAY_SIZE(aoclk_cec_32k_table) ; ++i)
		if (aoclk_cec_32k_table[i].parent_rate == prate &&
		    aoclk_cec_32k_table[i].target_rate == rate)
			return &aoclk_cec_32k_table[i];

	return NULL;
}
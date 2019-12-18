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
struct pll_rate {unsigned long rate; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct pll_rate const*) ; 
 struct pll_rate const* freqtbl ; 

__attribute__((used)) static const struct pll_rate *find_rate(unsigned long rate)
{
	int i;
	for (i = 1; i < ARRAY_SIZE(freqtbl); i++)
		if (rate > freqtbl[i].rate)
			return &freqtbl[i-1];
	return &freqtbl[i-1];
}
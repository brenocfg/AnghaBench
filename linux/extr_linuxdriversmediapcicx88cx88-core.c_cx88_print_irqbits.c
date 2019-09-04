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

/* Variables and functions */
 int /*<<< orphan*/  dprintk0 (char*,char const*,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

void cx88_print_irqbits(const char *tag, const char *strings[],
			int len, u32 bits, u32 mask)
{
	unsigned int i;

	dprintk0("%s [0x%x]", tag, bits);
	for (i = 0; i < len; i++) {
		if (!(bits & (1 << i)))
			continue;
		if (strings[i])
			pr_cont(" %s", strings[i]);
		else
			pr_cont(" %d", i);
		if (!(mask & (1 << i)))
			continue;
		pr_cont("*");
	}
	pr_cont("\n");
}
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
typedef  enum mac8390_access { ____Placeholder_mac8390_access } mac8390_access ;

/* Variables and functions */
 int ACCESS_16 ; 
 int ACCESS_32 ; 
 int ACCESS_UNKNOWN ; 
 int nubus_readl (unsigned long) ; 
 int /*<<< orphan*/  nubus_writel (int,unsigned long) ; 
 int /*<<< orphan*/  word_memcpy_fromcard (int*,unsigned long,int) ; 
 int /*<<< orphan*/  word_memcpy_tocard (unsigned long,int*,int) ; 

__attribute__((used)) static enum mac8390_access mac8390_testio(unsigned long membase)
{
	u32 outdata = 0xA5A0B5B0;
	u32 indata = 0;

	/* Try writing 32 bits */
	nubus_writel(outdata, membase);
	/* Now read it back */
	indata = nubus_readl(membase);
	if (outdata == indata)
		return ACCESS_32;

	outdata = 0xC5C0D5D0;
	indata = 0;

	/* Write 16 bit output */
	word_memcpy_tocard(membase, &outdata, 4);
	/* Now read it back */
	word_memcpy_fromcard(&indata, membase, 4);
	if (outdata == indata)
		return ACCESS_16;

	return ACCESS_UNKNOWN;
}
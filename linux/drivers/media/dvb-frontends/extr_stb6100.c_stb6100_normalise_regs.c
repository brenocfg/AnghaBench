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
typedef  int u8 ;
struct TYPE_2__ {int mask; int set; } ;

/* Variables and functions */
 int STB6100_NUMREGS ; 
 TYPE_1__* stb6100_template ; 

__attribute__((used)) static inline void stb6100_normalise_regs(u8 regs[])
{
	int i;

	for (i = 0; i < STB6100_NUMREGS; i++)
		regs[i] = (regs[i] & stb6100_template[i].mask) | stb6100_template[i].set;
}
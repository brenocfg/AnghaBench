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
struct TYPE_2__ {unsigned int kscratch_mask; int /*<<< orphan*/  conf; } ;
struct cpuinfo_mips {TYPE_1__ guest; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 unsigned int MIPS_CONF4_KSCREXIST ; 
 unsigned int MIPS_CONF4_KSCREXIST_SHIFT ; 
 unsigned int MIPS_CONF_M ; 
 int /*<<< orphan*/  probe_gc0_config (unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline unsigned int decode_guest_config4(struct cpuinfo_mips *c)
{
	unsigned int config4;

	probe_gc0_config(config4, config4,
			 MIPS_CONF_M | MIPS_CONF4_KSCREXIST);

	c->guest.kscratch_mask = (config4 & MIPS_CONF4_KSCREXIST)
				>> MIPS_CONF4_KSCREXIST_SHIFT;

	if (config4 & MIPS_CONF_M)
		c->guest.conf |= BIT(5);
	return config4 & MIPS_CONF_M;
}
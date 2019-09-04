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
struct cpuinfo_mips {int dummy; } ;

/* Variables and functions */
 unsigned int decode_guest_config0 (struct cpuinfo_mips*) ; 
 unsigned int decode_guest_config1 (struct cpuinfo_mips*) ; 
 unsigned int decode_guest_config2 (struct cpuinfo_mips*) ; 
 unsigned int decode_guest_config3 (struct cpuinfo_mips*) ; 
 unsigned int decode_guest_config4 (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  decode_guest_config5 (struct cpuinfo_mips*) ; 

__attribute__((used)) static inline void decode_guest_configs(struct cpuinfo_mips *c)
{
	unsigned int ok;

	ok = decode_guest_config0(c);
	if (ok)
		ok = decode_guest_config1(c);
	if (ok)
		ok = decode_guest_config2(c);
	if (ok)
		ok = decode_guest_config3(c);
	if (ok)
		ok = decode_guest_config4(c);
	if (ok)
		decode_guest_config5(c);
}
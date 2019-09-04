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
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  phandle ;

/* Variables and functions */
 int /*<<< orphan*/  prom_getchild (int /*<<< orphan*/ ) ; 
 int prom_getint (int /*<<< orphan*/ ,char*) ; 
 unsigned long prom_getintdefault (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int prom_getproperty (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  prom_getsibling (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static unsigned long cpuid_to_freq(phandle node, int cpuid)
{
	bool is_cpu_node = false;
	unsigned long freq = 0;
	char type[128];

	if (!node)
		return freq;

	if (prom_getproperty(node, "device_type", type, sizeof(type)) != -1)
		is_cpu_node = (strcmp(type, "cpu") == 0);

	/* try upa-portid then cpuid to get cpuid, see prom_64.c */
	if (is_cpu_node && (prom_getint(node, "upa-portid") == cpuid ||
			    prom_getint(node, "cpuid") == cpuid))
		freq = prom_getintdefault(node, "clock-frequency", 0);
	if (!freq)
		freq = cpuid_to_freq(prom_getchild(node), cpuid);
	if (!freq)
		freq = cpuid_to_freq(prom_getsibling(node), cpuid);

	return freq;
}
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
struct cpuid {int /*<<< orphan*/  machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cpu_id (struct cpuid*) ; 
 int /*<<< orphan*/  sclp_early_printk (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  u16_to_hex (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_machine_type(void)
{
	static char mach_str[80] = "Detected machine-type number: ";
	char type_str[5];
	struct cpuid id;

	get_cpu_id(&id);
	u16_to_hex(type_str, id.machine);
	strcat(mach_str, type_str);
	strcat(mach_str, "\n");
	sclp_early_printk(mach_str);
}
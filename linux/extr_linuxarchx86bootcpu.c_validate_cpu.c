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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  check_cpu (int*,int*,int /*<<< orphan*/ **) ; 
 scalar_t__ check_knl_erratum () ; 
 char* cpu_name (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  show_cap_strs (int /*<<< orphan*/ *) ; 

int validate_cpu(void)
{
	u32 *err_flags;
	int cpu_level, req_level;

	check_cpu(&cpu_level, &req_level, &err_flags);

	if (cpu_level < req_level) {
		printf("This kernel requires an %s CPU, ",
		       cpu_name(req_level));
		printf("but only detected an %s CPU.\n",
		       cpu_name(cpu_level));
		return -1;
	}

	if (err_flags) {
		puts("This kernel requires the following features "
		     "not present on the CPU:\n");
		show_cap_strs(err_flags);
		putchar('\n');
		return -1;
	} else if (check_knl_erratum()) {
		return -1;
	} else {
		return 0;
	}
}
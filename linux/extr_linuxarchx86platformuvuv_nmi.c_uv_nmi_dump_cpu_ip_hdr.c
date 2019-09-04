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

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void uv_nmi_dump_cpu_ip_hdr(void)
{
	pr_info("\nUV: %4s %6s %-32s %s   (Note: PID 0 not listed)\n",
		"CPU", "PID", "COMMAND", "IP");
}
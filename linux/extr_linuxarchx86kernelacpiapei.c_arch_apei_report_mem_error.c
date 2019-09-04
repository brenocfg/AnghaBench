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
struct cper_sec_mem_err {int dummy; } ;

/* Variables and functions */

void arch_apei_report_mem_error(int sev, struct cper_sec_mem_err *mem_err)
{
#ifdef CONFIG_X86_MCE
	apei_mce_report_mem_error(sev, mem_err);
#endif
}
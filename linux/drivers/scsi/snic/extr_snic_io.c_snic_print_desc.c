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
 int SNIC_DESC_LOGGING ; 
 int /*<<< orphan*/  snic_dump_desc (char const*,char*,int) ; 
 int snic_log_level ; 

void
snic_print_desc(const char *fn, char *os_buf, int len)
{
	if (snic_log_level & SNIC_DESC_LOGGING)
		snic_dump_desc(fn, os_buf, len);
}
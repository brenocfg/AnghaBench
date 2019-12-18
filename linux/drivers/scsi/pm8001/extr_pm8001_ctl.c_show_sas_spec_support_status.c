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
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int SAS_1_1 ; 
 unsigned int SAS_2_0 ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t
show_sas_spec_support_status(unsigned int mode, char *buf)
{
	ssize_t len = 0;

	if (mode & SAS_1_1)
		len = sprintf(buf, "%s", "SAS1.1");
	if (mode & SAS_2_0)
		len += sprintf(buf + len, "%s%s", len ? ", " : "", "SAS2.0");
	len += sprintf(buf + len, "\n");

	return len;
}
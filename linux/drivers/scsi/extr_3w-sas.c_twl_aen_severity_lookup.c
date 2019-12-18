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
 scalar_t__ TW_AEN_SEVERITY_DEBUG ; 
 scalar_t__ TW_AEN_SEVERITY_ERROR ; 
 char** twl_aen_severity_table ; 

__attribute__((used)) static char *twl_aen_severity_lookup(unsigned char severity_code)
{
	char *retval = NULL;

	if ((severity_code < (unsigned char) TW_AEN_SEVERITY_ERROR) ||
	    (severity_code > (unsigned char) TW_AEN_SEVERITY_DEBUG))
		goto out;

	retval = twl_aen_severity_table[severity_code];
out:
	return retval;
}
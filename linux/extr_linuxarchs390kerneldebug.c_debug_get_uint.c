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
 int EINVAL ; 
 int simple_strtoul (char*,char**,int) ; 
 char* skip_spaces (char*) ; 

__attribute__((used)) static inline int debug_get_uint(char *buf)
{
	int rc;

	buf = skip_spaces(buf);
	rc = simple_strtoul(buf, &buf, 10);
	if (*buf)
		rc = -EINVAL;
	return rc;
}
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
 unsigned int ARRAY_SIZE (char const* const*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static char *is_dc_name(char *buf, size_t bsize, unsigned int source)
{
	static const char * const dc_int_names[] = {
		"common",
		"lcb",
		"8051",
		"lbm"	/* local block merge */
	};

	if (source < ARRAY_SIZE(dc_int_names))
		snprintf(buf, bsize, "dc_%s_int", dc_int_names[source]);
	else
		snprintf(buf, bsize, "DCInt%u", source);
	return buf;
}
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
 unsigned long ARRAY_SIZE (char**) ; 
 char** trap_description ; 

const char *trap_name(unsigned long code)
{
	const char *t = NULL;

	if (code < ARRAY_SIZE(trap_description))
		t = trap_description[code];

	return t ? t : "Unknown trap";
}
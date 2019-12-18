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
typedef  char u_char ;

/* Variables and functions */
 int simple_strtoul (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  skip_spaces (char*) ; 

char *spk_s2uchar(char *start, char *dest)
{
	int val;

	/* Do not replace with kstrtoul: here we need start to be updated */
	val = simple_strtoul(skip_spaces(start), &start, 10);
	if (*start == ',')
		start++;
	*dest = (u_char)val;
	return start;
}
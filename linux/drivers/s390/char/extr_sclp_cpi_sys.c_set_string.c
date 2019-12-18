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
 size_t CPI_LENGTH_NAME ; 
 size_t strlen (char const*) ; 
 char toupper (char const) ; 

__attribute__((used)) static void set_string(char *attr, const char *value)
{
	size_t len;
	size_t i;

	len = strlen(value);

	if ((len > 0) && (value[len - 1] == '\n'))
		len--;

	for (i = 0; i < CPI_LENGTH_NAME; i++) {
		if (i < len)
			attr[i] = toupper(value[i]);
		else
			attr[i] = ' ';
	}
}
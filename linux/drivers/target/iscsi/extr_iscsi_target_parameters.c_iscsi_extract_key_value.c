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
 int /*<<< orphan*/  pr_err (char*) ; 
 char* strchr (char*,char) ; 

int iscsi_extract_key_value(char *textbuf, char **key, char **value)
{
	*value = strchr(textbuf, '=');
	if (!*value) {
		pr_err("Unable to locate \"=\" separator for key,"
				" ignoring request.\n");
		return -1;
	}

	*key = textbuf;
	**value = '\0';
	*value = *value + 1;

	return 0;
}
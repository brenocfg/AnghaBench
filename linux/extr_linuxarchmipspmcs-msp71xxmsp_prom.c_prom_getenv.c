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
 char** prom_envp ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

char *prom_getenv(char *env_name)
{
	/*
	 * Return a pointer to the given environment variable.	prom_envp
	 * points to a null terminated array of pointers to variables.
	 * Environment variables are stored in the form of "memsize=64"
	 */

	char **var = prom_envp;
	int i = strlen(env_name);

	while (*var) {
		if (strncmp(env_name, *var, i) == 0) {
			return *var + strlen(env_name) + 1;
		}
		var++;
	}

	return NULL;
}
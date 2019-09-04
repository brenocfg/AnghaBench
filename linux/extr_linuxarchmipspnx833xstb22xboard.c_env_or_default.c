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
 char* prom_getenv (char*) ; 
 unsigned long simple_strtol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long env_or_default(char *env, unsigned long dfl)
{
	char *str = prom_getenv(env);
	return str ? simple_strtol(str, 0, 0) : dfl;
}
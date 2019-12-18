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
 char* nvkm_stropt (char const*,char const*,int*) ; 
 int /*<<< orphan*/  strncasecmpz (char const*,char*,int) ; 

bool
nvkm_boolopt(const char *optstr, const char *opt, bool value)
{
	int arglen;

	optstr = nvkm_stropt(optstr, opt, &arglen);
	if (optstr) {
		if (!strncasecmpz(optstr, "0", arglen) ||
		    !strncasecmpz(optstr, "no", arglen) ||
		    !strncasecmpz(optstr, "off", arglen) ||
		    !strncasecmpz(optstr, "false", arglen))
			value = false;
		else
		if (!strncasecmpz(optstr, "1", arglen) ||
		    !strncasecmpz(optstr, "yes", arglen) ||
		    !strncasecmpz(optstr, "on", arglen) ||
		    !strncasecmpz(optstr, "true", arglen))
			value = true;
	}

	return value;
}
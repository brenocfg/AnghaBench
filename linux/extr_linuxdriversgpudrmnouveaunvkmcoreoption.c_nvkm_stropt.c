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
 int strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strncasecmpz (char const*,char const*,int) ; 

const char *
nvkm_stropt(const char *optstr, const char *opt, int *arglen)
{
	while (optstr && *optstr != '\0') {
		int len = strcspn(optstr, ",=");
		switch (optstr[len]) {
		case '=':
			if (!strncasecmpz(optstr, opt, len)) {
				optstr += len + 1;
				*arglen = strcspn(optstr, ",=");
				return *arglen ? optstr : NULL;
			}
			optstr++;
			break;
		case ',':
			optstr++;
			break;
		default:
			break;
		}
		optstr += len;
	}

	return NULL;
}
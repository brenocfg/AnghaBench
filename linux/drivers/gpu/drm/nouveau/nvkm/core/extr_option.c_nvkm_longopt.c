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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,int,int /*<<< orphan*/ ) ; 
 int kstrtol (char*,int /*<<< orphan*/ ,long*) ; 
 char* nvkm_stropt (char const*,char const*,int*) ; 

long
nvkm_longopt(const char *optstr, const char *opt, long value)
{
	long result = value;
	int arglen;
	char *s;

	optstr = nvkm_stropt(optstr, opt, &arglen);
	if (optstr && (s = kstrndup(optstr, arglen, GFP_KERNEL))) {
		int ret = kstrtol(s, 0, &value);
		if (ret == 0)
			result = value;
		kfree(s);
	}

	return result;
}
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
 int EINVAL ; 
 int cdpl2_enable () ; 
 int cdpl3_enable () ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int set_mba_sc (int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int parse_rdtgroupfs_options(char *data)
{
	char *token, *o = data;
	int ret = 0;

	while ((token = strsep(&o, ",")) != NULL) {
		if (!*token) {
			ret = -EINVAL;
			goto out;
		}

		if (!strcmp(token, "cdp")) {
			ret = cdpl3_enable();
			if (ret)
				goto out;
		} else if (!strcmp(token, "cdpl2")) {
			ret = cdpl2_enable();
			if (ret)
				goto out;
		} else if (!strcmp(token, "mba_MBps")) {
			ret = set_mba_sc(true);
			if (ret)
				goto out;
		} else {
			ret = -EINVAL;
			goto out;
		}
	}

	return 0;

out:
	pr_err("Invalid mount option \"%s\"\n", token);

	return ret;
}
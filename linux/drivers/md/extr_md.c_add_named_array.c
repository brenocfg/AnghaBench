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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int DISK_NAME_LEN ; 
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  MD_MAJOR ; 
 unsigned long MINORMASK ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ kstrtoul (char*,int,unsigned long*) ; 
 int md_alloc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int add_named_array(const char *val, const struct kernel_param *kp)
{
	/*
	 * val must be "md_*" or "mdNNN".
	 * For "md_*" we allocate an array with a large free minor number, and
	 * set the name to val.  val must not already be an active name.
	 * For "mdNNN" we allocate an array with the minor number NNN
	 * which must not already be in use.
	 */
	int len = strlen(val);
	char buf[DISK_NAME_LEN];
	unsigned long devnum;

	while (len && val[len-1] == '\n')
		len--;
	if (len >= DISK_NAME_LEN)
		return -E2BIG;
	strlcpy(buf, val, len+1);
	if (strncmp(buf, "md_", 3) == 0)
		return md_alloc(0, buf);
	if (strncmp(buf, "md", 2) == 0 &&
	    isdigit(buf[2]) &&
	    kstrtoul(buf+2, 10, &devnum) == 0 &&
	    devnum <= MINORMASK)
		return md_alloc(MKDEV(MD_MAJOR, devnum), NULL);

	return -EINVAL;
}
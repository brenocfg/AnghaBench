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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int snprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static void report_msg_status(int reset, int received, int used,
			      int rejected, char *groupname)
{
	int len;
	char buf[160];

	if (reset) {
		pr_info("i18n messages from group %s reset to defaults\n",
			groupname);
	} else if (received) {
		len = snprintf(buf, sizeof(buf),
			       " updated %d of %d i18n messages from group %s\n",
				       used, received, groupname);
		if (rejected)
			snprintf(buf + (len - 1), sizeof(buf) - (len - 1),
				 " with %d reject%s\n",
				 rejected, rejected > 1 ? "s" : "");
		pr_info("%s", buf);
	}
}
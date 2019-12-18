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
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 int snprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static void report_char_chartab_status(int reset, int received, int used,
				       int rejected, int do_characters)
{
	static char const *object_type[] = {
		"character class entries",
		"character descriptions",
	};
	int len;
	char buf[80];

	if (reset) {
		pr_info("%s reset to defaults\n", object_type[do_characters]);
	} else if (received) {
		len = snprintf(buf, sizeof(buf),
			       " updated %d of %d %s\n",
			       used, received, object_type[do_characters]);
		if (rejected)
			snprintf(buf + (len - 1), sizeof(buf) - (len - 1),
				 " with %d reject%s\n",
				 rejected, rejected > 1 ? "s" : "");
		pr_info("%s", buf);
	}
}
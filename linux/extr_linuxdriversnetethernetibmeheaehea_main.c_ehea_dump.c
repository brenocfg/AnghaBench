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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ehea_dump(void *adr, int len, char *msg)
{
	int x;
	unsigned char *deb = adr;
	for (x = 0; x < len; x += 16) {
		pr_info("%s adr=%p ofs=%04x %016llx %016llx\n",
			msg, deb, x, *((u64 *)&deb[0]), *((u64 *)&deb[8]));
		deb += 16;
	}
}
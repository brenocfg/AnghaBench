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
typedef  int u8 ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t sprintf_ipaddr(char *buf, u8 *ip)
{
	char *str = buf;

	if (ip[0] == 0 && ip[1] == 0 && ip[2] == 0 && ip[3] == 0 &&
	    ip[4] == 0 && ip[5] == 0 && ip[6] == 0 && ip[7] == 0 &&
	    ip[8] == 0 && ip[9] == 0 && ip[10] == 0xff && ip[11] == 0xff) {
		/*
		 * IPV4
		 */
		str += sprintf(buf, "%pI4", ip + 12);
	} else {
		/*
		 * IPv6
		 */
		str += sprintf(str, "%pI6", ip);
	}
	str += sprintf(str, "\n");
	return str - buf;
}
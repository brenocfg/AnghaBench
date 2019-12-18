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
struct device_driver {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpcmd (char const*,char*,int,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

__attribute__((used)) static ssize_t recording_status_show(struct device_driver *driver, char *buf)
{
	static const char cp_command[] = "QUERY RECORDING ";
	int len;

	cpcmd(cp_command, buf, 4096, NULL);
	len = strlen(buf);
	return len;
}
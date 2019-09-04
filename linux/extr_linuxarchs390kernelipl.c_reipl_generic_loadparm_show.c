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
struct ipl_parameter_block {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOADPARM_LEN ; 
 int /*<<< orphan*/  reipl_get_ascii_loadparm (char*,struct ipl_parameter_block*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t reipl_generic_loadparm_show(struct ipl_parameter_block *ipb,
					   char *page)
{
	char buf[LOADPARM_LEN + 1];

	reipl_get_ascii_loadparm(buf, ipb);
	return sprintf(page, "%s\n", buf);
}
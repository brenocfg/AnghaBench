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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIVA_BUILD ; 
 int /*<<< orphan*/  DRIVERLNAME ; 
 int /*<<< orphan*/  DRIVERNAME ; 
 int /*<<< orphan*/  DRIVERRELEASE_DIDD ; 
 int /*<<< orphan*/  diva_didd_common_code_build ; 
 int /*<<< orphan*/  getrev (char*) ; 
 int /*<<< orphan*/  main_revision ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int divadidd_proc_show(struct seq_file *m, void *v)
{
	char tmprev[32];

	strcpy(tmprev, main_revision);
	seq_printf(m, "%s\n", DRIVERNAME);
	seq_printf(m, "name     : %s\n", DRIVERLNAME);
	seq_printf(m, "release  : %s\n", DRIVERRELEASE_DIDD);
	seq_printf(m, "build    : %s(%s)\n",
		   diva_didd_common_code_build, DIVA_BUILD);
	seq_printf(m, "revision : %s\n", getrev(tmprev));

	return 0;
}
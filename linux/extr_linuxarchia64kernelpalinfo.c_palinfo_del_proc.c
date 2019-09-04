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
 int /*<<< orphan*/  palinfo_dir ; 
 int /*<<< orphan*/  remove_proc_subtree (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static int palinfo_del_proc(unsigned int hcpu)
{
	char cpustr[3+4+1];	/* cpu numbers are up to 4095 on itanic */

	sprintf(cpustr, "cpu%d", hcpu);
	remove_proc_subtree(cpustr, palinfo_dir);
	return 0;
}
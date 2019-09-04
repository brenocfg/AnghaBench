#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dcss_segment {int segcnt; TYPE_1__* range; } ;
struct TYPE_2__ {int start; int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACHINE_IS_VM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  cpcmd (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dcss_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct dcss_segment* segment_by_name (char*) ; 
 int /*<<< orphan*/ * segtype_string ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int strlen (char*) ; 

void
segment_save(char *name)
{
	struct dcss_segment *seg;
	char cmd1[160];
	char cmd2[80];
	int i, response;

	if (!MACHINE_IS_VM)
		return;

	mutex_lock(&dcss_lock);
	seg = segment_by_name (name);

	if (seg == NULL) {
		pr_err("Saving unknown DCSS %s failed\n", name);
		goto out;
	}

	sprintf(cmd1, "DEFSEG %s", name);
	for (i=0; i<seg->segcnt; i++) {
		sprintf(cmd1+strlen(cmd1), " %lX-%lX %s",
			seg->range[i].start >> PAGE_SHIFT,
			seg->range[i].end >> PAGE_SHIFT,
			segtype_string[seg->range[i].start & 0xff]);
	}
	sprintf(cmd2, "SAVESEG %s", name);
	response = 0;
	cpcmd(cmd1, NULL, 0, &response);
	if (response) {
		pr_err("Saving a DCSS failed with DEFSEG response code "
		       "%i\n", response);
		goto out;
	}
	cpcmd(cmd2, NULL, 0, &response);
	if (response) {
		pr_err("Saving a DCSS failed with SAVESEG response code "
		       "%i\n", response);
		goto out;
	}
out:
	mutex_unlock(&dcss_lock);
}
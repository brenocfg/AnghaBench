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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  TELEM_IOSS ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int telemetry_get_trace_verbosity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int telem_ioss_trc_verb_show(struct seq_file *s, void *unused)
{
	u32 verbosity;
	int err;

	err = telemetry_get_trace_verbosity(TELEM_IOSS, &verbosity);
	if (err) {
		pr_err("Get IOSS Trace Verbosity Failed with Error %d\n", err);
		return -EFAULT;
	}

	seq_printf(s, "IOSS Trace Verbosity %u\n", verbosity);
	return 0;
}
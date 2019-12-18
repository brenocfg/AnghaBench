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
 int /*<<< orphan*/  cch_seq_ops ; 
 int /*<<< orphan*/  gru_seq_ops ; 
 int /*<<< orphan*/  mcs_statistics_fops ; 
 int /*<<< orphan*/  options_fops ; 
 int /*<<< orphan*/  proc_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_create_seq (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_gru ; 
 int /*<<< orphan*/  proc_mkdir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_proc_subtree (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  statistics_fops ; 

int gru_proc_init(void)
{
	proc_gru = proc_mkdir("sgi_uv/gru", NULL);
	if (!proc_gru)
		return -1;
	if (!proc_create("statistics", 0644, proc_gru, &statistics_fops))
		goto err;
	if (!proc_create("mcs_statistics", 0644, proc_gru, &mcs_statistics_fops))
		goto err;
	if (!proc_create("debug_options", 0644, proc_gru, &options_fops))
		goto err;
	if (!proc_create_seq("cch_status", 0444, proc_gru, &cch_seq_ops))
		goto err;
	if (!proc_create_seq("gru_status", 0444, proc_gru, &gru_seq_ops))
		goto err;
	return 0;
err:
	remove_proc_subtree("sgi_uv/gru", NULL);
	return -1;
}
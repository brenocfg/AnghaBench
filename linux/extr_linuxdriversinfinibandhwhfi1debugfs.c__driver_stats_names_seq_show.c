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
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hfi1_statnames ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _driver_stats_names_seq_show(struct seq_file *s, void *v)
{
	loff_t *spos = v;

	seq_printf(s, "%s\n", hfi1_statnames[*spos]);
	return 0;
}